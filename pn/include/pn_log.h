#pragma once

#define LOG_DECLARATION(name) void name(const char* format, ...)

LOG_DECLARATION(pn_log);
LOG_DECLARATION(pn_error);
LOG_DECLARATION(pn_warn);
LOG_DECLARATION(pn_debug);