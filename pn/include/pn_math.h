#pragma once

#include "pn_common.h"    
#define PN_PI 3.1415926535897932384626433832795

f64 pn_deg2rad(f64 deg);
f64 pn_rad2deg(f64 rad);
void pn_gl_perspective(f64 fov, f64 aspect, f64 znear, f64 zfar);