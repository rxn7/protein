#include "pn_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define PN_START_VARGS(start) \
    va_list args;\
    va_start(args, start);

#define PN_END_VARGS() \
    va_end(args);

// TODO: Add [LOG] prefix and '\n'
void pn_log(const char* format, ...){
    PN_START_VARGS(format);

    char text[4096];
    strcpy(text, "[LOG] ");
    strcat(text, format);
    strcat(text, "\n");

    vprintf(text, args);
    PN_END_VARGS();
}