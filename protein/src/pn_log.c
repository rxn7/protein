#include "pn_log.h"
#include <stdarg.h>
#include <stdio.h>

#define PN_START_VARGS(start) \
    va_list args;\
    va_start(args, start);

#define PN_END_VARGS() \
    va_end(args);

// TODO: Add [LOG] prefix and '\n'
void pn_log(const char* format, ...){
    PN_START_VARGS(format);
    vprintf(format, args);
    PN_END_VARGS();
}