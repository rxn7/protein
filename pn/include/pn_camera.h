#pragma once

#include "pn_common.h"
#include "pn_math.h"

typedef struct {
	mat4 m_projection, m_view;
	f32 m_pitch, m_yaw, m_znear, m_zfar, m_fov;
	v3 m_forward, m_up, m_right, m_pos;
} pn_camera_t;

pn_camera_t* pn_camera_create(vec3 pos, f32 fov, f32 znear, f32 zfar);

void pn_camera_update(void);
void pn_camera_move(vec3 move_dir);
void pn_camera_rotate(f32 yaw, f32 pitch);
void pn_camera_free(pn_camera_t* camera);