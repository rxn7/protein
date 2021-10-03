#include "pn_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define PN_START_VARGS(start)\
    va_list args;\
    va_start(args, start);

#define PN_END_VARGS()\
    va_end(args);

#define PN_PRINT_ARGS(type)\
    printf("[" type "]");\
    vprintf(format, args);\
    printf("\n");
 
#define PN_LOG_DEFINITION(func_name, type)\
    LOG_DECLARATION(func_name) {\
        PN_START_VARGS(format);\
        PN_PRINT_ARGS(type);\
        PN_END_VARGS(); }

PN_LOG_DEFINITION(pn_log, "LOG")
PN_LOG_DEFINITION(pn_error, "ERROR")
PN_LOG_DEFINITION(pn_warn, "WARN")
PN_LOG_DEFINITION(pn_debug, "DEBUG")