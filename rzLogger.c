#define _POSIX_C_SOURCE 199309L
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h> 
#include <unistd.h>
#include <string.h>
#include "rzLogger.h"

static pthread_t logger_th;
static __int8_t init = 0;
static rz_logger_level_t currentLevel = RZ_LOG_INFO;


typedef struct 
{   
    char buffer [1024];
    rz_logger_level_t level;
    struct timespec timestamp;
} log_entry_t;

#define QUEUE_SIZE 1000

static log_entry_t log_queue[QUEUE_SIZE];
static int queue_head = 0, queue_tail = 0;
static pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

const char* level2Str(rz_logger_level_t level)
{
    switch (level)
    {
    case RZ_LOG_ERROR:
        return " ERROR ";
    case RZ_LOG_WARN:
        return "WARNING";
    case RZ_LOG_INFO:
        return " INFO. ";
    case RZ_LOG_DEBUG:
        return " DEBUG ";
    case RZ_LOG_DEBUG_EXTRA:
        return "DEBUG +";
    default:
        return "?";
    }
}

// Hilo logger
void* logger_thread_func(void* arg) 
{
    (void)arg;
    while (init) 
    {
        /*1: Hay mensajes en la cola?*/
        pthread_mutex_lock(&queue_mutex);
        
        if(queue_head != queue_tail)
        {
            log_entry_t entry = log_queue[queue_tail];
            queue_tail = (queue_tail + 1) % QUEUE_SIZE;
            pthread_mutex_unlock(&queue_mutex);

            char timestamp[32];
            strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&entry.timestamp.tv_sec));
            printf("[%s][%s] %s\n", timestamp, level2Str(entry.level), entry.buffer);
            fflush(stdout);  // Forzar salida inmediata
        }
        else
        {
            pthread_mutex_unlock(&queue_mutex);
            struct timespec ts = {0, 1000000}; // 1 ms = 1,000,000 ns
            nanosleep(&ts, NULL);
        }
    }
    return NULL;
}

void rzLog_init()
{

    // Resetear cola
    queue_head = 0;
    queue_tail = 0;
    
    init = 1;

    pthread_create(&logger_th, NULL, logger_thread_func, NULL);
}

void rzLog_stop()
{
    if(!init)
        return;

    init = 0;

    pthread_join(logger_th, NULL);
}

void rzLog_set_level(rz_logger_level_t level)
{
    currentLevel = level;
}

void rzLog_set_output(const char* filename)
{
    (void)filename; 
}

void rzLog(rz_logger_level_t level, const char* format, ...)
{
    if(currentLevel < level)
    {
        return;
    }

    // 2. Formatear el mensaje usando argumentos variables
    char buffer[1024];
    va_list args;                    // Lista de argumentos variables
    va_start(args, format);          // Inicializar lista después de 'format'
    vsnprintf(buffer, sizeof(buffer), format, args);  // Como sprintf pero con va_list
    va_end(args);                    // Limpiar lista
    
    // 3. Crear entrada para la cola
    log_entry_t entry;
    strncpy(entry.buffer, buffer, sizeof(entry.buffer) - 1);
    entry.buffer[sizeof(entry.buffer) - 1] = '\0';  // Terminar string
    entry.level = level;
    clock_gettime(CLOCK_REALTIME, &entry.timestamp);  // Timestamp actual

        
    // 4. Meter en cola thread-safe
    pthread_mutex_lock(&queue_mutex);
    
    // Verificar que la cola no esté llena
    int next_head = (queue_head + 1) % QUEUE_SIZE;
    if (next_head != queue_tail) {  // No está llena
        log_queue[queue_head] = entry;
        queue_head = next_head;
    }
    // Si está llena, se pierde el mensaje (o podrías sobrescribir el más viejo)
    
    pthread_mutex_unlock(&queue_mutex);

}