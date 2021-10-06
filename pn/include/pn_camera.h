#pragma once

#include "pn_common.h"
#include <cglm/cglm.h>

typedef struct {
	mat4 m_projection;
	mat4 m_view;

	vec3 m_pos;

	f32 m_pitch, m_yaw;
	
	vec3 m_forward, m_up, m_right;
} pn_camera_t;

pn_camera_t* pn_create_camera(vec3 pos, float fov, float znear, float zfar);

void pn_update_camera();

void pn_move_camera(vec3 move_dir, bool normalize);

void pn_free_camera(pn_camera_t* camera);