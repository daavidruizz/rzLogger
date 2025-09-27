#ifndef RZ_LOGGER_H
#define RZ_LOGGER_H


typedef enum {
    RZ_LOG_ERROR        = 1,
    RZ_LOG_WARN         = 2,
    RZ_LOG_INFO         = 3,
    RZ_LOG_DEBUG        = 4,
    RZ_LOG_DEBUG_EXTRA  = 5
} rz_logger_level_t;

void rzLog(rz_logger_level_t level, const char* format, ...);

void rzLog_init();
void rzLog_stop();
void rzLog_set_level(rz_logger_level_t min_level); // NULL to ENV variable
void rzLog_set_output(const char* filename); //NULL to console

#endif