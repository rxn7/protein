#pragma once

#include "pn_common.h"

typedef struct {
	mat4 m_proj_mat;
} pn_camera_t;

void pn_calc_cam_perspective(f32 fov, f32 znear, f32 zfar, pn_camera_t* cam);