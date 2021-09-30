#pragma once

#include "pn_common.h"

#define PN_RGBA_8(col) col.r, col.g, col.b, col.a
#define PN_RGBA_F32(col) (f32)col.r / 255, (f32)col.g / 255, (f32)col.b / 255, (f32)col.a / 255

typedef struct { u8 r, g, b, a; } pn_color_t;