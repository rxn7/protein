#pragma once

#include "pn_common.h"    
#define PN_PI 3.1415926535897932384626433832795

typedef f32 v3[3];
typedef f32 v2[2];

static const v3 PN_V3_ONE_X = {1, 0, 0};
static const v3 PN_V3_ONE_Y = {0, 1, 0};
static const v3 PN_V3_ONE_Z = {0, 0, 1};

#define PN_DEG_TO_RAD(x) x * (PN_PI / 180.0f)

// TODO: Delete cglm when all of the important functions in pn_math are complete.

f32 pn_v2_get_magnitude(v2 vec);
f32 pn_v3_get_magnitude(v3 vec);

void pn_v2_normalize(v2 vec);
void pn_v3_normalize(v3 vec);

void pn_v2_set(v2 vec, v2 value);
void pn_v3_set(v3 vec, v3 value);

void pn_v2_mult_each(v2 vec, f32 value);
void pn_v3_mult_each(v3 vec, f32 value);

void pn_v2_div_each(v2 vec, f32 value);
void pn_v3_div_each(v3 vec, f32 value);

void pn_v2_add(v2 a, v2 b, v2 dest);
void pn_v2_sub(v2 a, v2 b, v2 dest);

void pn_v3_add(v3 a, v3 b, v3 dest);
void pn_v3_sub(v3 a, v3 b, v3 dest);

void pn_v3_cross(v3 a, v3 b, v3 dest);

void pn_v3_normal(v3 a, v3 b, v3 c, v3 dest);
