#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

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
    b8 is_error = level < LOG_LEVEL_WARNING;

    // Do this to create message on stack and not dynamically
    const i32 msg_length = 32000;
    char out_message[msg_length];
    memset(out_message, 0, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, msg_length, message, arg_ptr);
    va_end(arg_ptr);

    char final_out_message[msg_length];
    memset(final_out_message, 0, sizeof(final_out_message));
    sprintf(final_out_message, "%s%s\n", level_strings[level], out_message);

    if (is_error) {
        platform_console_write_error(final_out_message, level);
    } else {
        platform_console_write(final_out_message, level);
    }
}