# rzLogger

`rzLogger` es un logger simple, portable y thread-safe para proyectos en C/C++. Permite registrar mensajes de diferentes niveles (ERROR, WARNING, INFO, DEBUG, etc.) desde múltiples hilos, gestionando una cola interna y un hilo dedicado para la salida de logs.

## Características

- **Thread-safe:** múltiples hilos pueden registrar mensajes simultáneamente.
- **Cola interna:** los mensajes se almacenan en una cola circular y se procesan en segundo plano.
- **Niveles de log:** ERROR, WARNING, INFO, DEBUG, DEBUG EXTRA.
- **Salida por consola:** los mensajes se imprimen en consola con timestamp y nivel.
- **Fácil integración:** solo necesitas incluir los archivos fuente y cabecera.

## Uso básico

```c
#include "rzLogger.h"

int main() {
    rzLog_init(); // Inicializa el logger

    rzLog_set_level(RZ_LOG_DEBUG); // Establece el nivel mínimo de log

    rzLog(RZ_LOG_INFO, "Iniciando rzLogger. PID: %d", getpid());
    rzLog(RZ_LOG_DEBUG, "Mensaje de depuración: %s", "debug info");
    rzLog(RZ_LOG_ERROR, "Error detectado: código %d", -1);

    // Espera para asegurar que los mensajes se impriman
    sleep(2);

    rzLog_stop(); // Detiene el logger y libera recursos
    return 0;
}
```

## API

```c
void rzLog_init();
Inicializa el logger y lanza el hilo de procesamiento.

void rzLog_stop();
Detiene el logger y espera a que se procesen todos los mensajes.

void rzLog_set_level(rz_logger_level_t level);
Establece el nivel mínimo de mensajes a mostrar.

void rzLog(rz_logger_level_t level, const char* format, ...);
Registra un mensaje con formato y nivel especificado.
```

## Niveles de log

```c
typedef enum {
    RZ_LOG_ERROR,
    RZ_LOG_WARN,
    RZ_LOG_INFO,
    RZ_LOG_DEBUG,
    RZ_LOG_DEBUG_EXTRA
} rz_logger_level_t;
```

## Integración

- Copia rzLogger.c y rzLogger.h en tu proyecto.
- Incluye rzLogger.h en tus archivos fuente.
- Compila ambos archivos juntos.