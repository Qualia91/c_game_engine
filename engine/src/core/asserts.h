#pragma once

#include "defines.h"

// DIsable assertions by commenting out this line
#define KASSERTIONS_ENABLED

#ifdef KASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

KAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define KASSERT_RETURN(expr, return_val)                             \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            return return_val;                                       \
        }                                                            \
    }

#define KASSERT_MSG_RETURN(expr, message, return_val)                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            KFATAL(message);                                         \
            return return_val;                                       \
        }                                                            \
    }

#define KASSERT_NOT_NULL(expr, message, return_val)                  \
    {                                                                \
        if (!expr) {                                                  \
            KFATAL(message);                                         \
            return return_val;                                       \
        }                                                            \
    }

#define KASSERT(expr)                                                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }

#define KASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG
#define KASSERT_DEBUG(expr)                                          \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }

#else
#define KASSERT_DEBUG(expr)
#endif

#else
#define KASSERT(expr)
#define KASSERT_MESSAGE(expr, message)
#define KASSERT_DEBUG(expr)
#endif