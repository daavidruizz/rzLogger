#include "rzLogger.h"
#include <unistd.h>
int main() {

    int client_id = 0, chat_id = 5;
    
    rzLog_init();
    rzLog_set_level(RZ_LOG_DEBUG);
    
    rzLog(RZ_LOG_INFO, "Iniciando rzLogger en modo demostración. PID: %d", getpid());

    rzLog(RZ_LOG_DEBUG, "Cliente creado con ID: %d", client_id);
    rzLog(RZ_LOG_INFO, "Conectando al chat con ID: %d", chat_id);

    rzLog(RZ_LOG_WARN, "Advertencia: conexión lenta detectada en el chat %d", chat_id);

    rzLog(RZ_LOG_ERROR, "No se pudo enviar el mensaje: '%s' (código de error: %d)", "Hola mundo", -1);

    rzLog(RZ_LOG_DEBUG, "Finalizando ejemplo de uso de rzLogger.");
    
    sleep(3);
    rzLog_stop();
}