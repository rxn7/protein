#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cglm/cglm.h>
static const vec3 PN_V3_ONE_X = {1, 0, 0};
static const vec3 PN_V3_ONE_Y = {0, 1, 0};
static const vec3 PN_V3_ONE_Z = {0, 0, 1};

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t  i64;
typedef int32_t  i32;
typedef int16_t  i16;
typedef int8_t   i8;

typedef float f32;
typedef double f64;
typedef long double f96;