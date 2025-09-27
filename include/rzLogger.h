#ifndef RZ_LOGGER_H
#define RZ_LOGGER_H

#define rzLog(level, format, ...) \
    rzLog_impl(level, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

#define rzERROR(format, ...) rzTraza(RZ_TRACE_ERROR, format, ##__VA_ARGS__)
#define rzWARN(format, ...)  rzTraza(RZ_TRACE_WARN,  format, ##__VA_ARGS__)  
#define rzINFO(format, ...)  rzTraza(RZ_TRACE_INFO,  format, ##__VA_ARGS__)
#define rzDEBUG(format, ...) rzTraza(RZ_TRACE_DEBUG, format, ##__VA_ARGS__)

typedef enum {
    RZ_LOG_ERROR        = 1,
    RZ_LOG_WARN         = 2,
    RZ_LOG_INFO         = 3,
    RZ_LOG_DEBUG        = 4,
    RZ_LOG_DEBUG_EXTRA  = 5
} rz_logger_level_t;

void rzLog_impl(rz_logger_level_t level, const char* file, int line, const char* func, const char* format, ...);

void rzLog_init();
void rzLog_stop();
void rzLog_set_level(rz_logger_level_t min_level); // NULL to ENV variable
void rzLog_set_output(const char* filename); //NULL to console

#endif