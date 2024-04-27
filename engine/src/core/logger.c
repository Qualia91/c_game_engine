#include "logger.h"
#include "asserts.h"

// TODO: TEMP
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion failure: %s, message: %s, in file: %s, line %d\n", expression, message, file, line);
}

b8 initialise_logging() {
    // TODO: Create log file
    return TRUE;
}

void shutdown_logging() {
    // TODO: cleanup and write up queued entries
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"[FATAL]:   ", "[ERROR]:   ", "[WARNING]: ", "[INFO]:    ", "[DEBUG]:   ", "[TRACE]:   "};
    // b8 is_error = level < 2;

    // Do this to create message on stack and not dynamically
    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char final_out_message[32000];
    memset(final_out_message, 0, sizeof(final_out_message));
    sprintf(final_out_message, "%s%s\n", level_strings[level], out_message);

    printf("%s", final_out_message);
}