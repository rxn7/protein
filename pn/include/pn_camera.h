#pragma once

#include <cglm/cglm.h>

typedef struct {
	mat4 m_perspective;
	vec3 m_pos;
	vec3 m_forward;
	vec3 m_up;
} pn_camera_t;

pn_camera_t* pn_create_camera(vec3 pos, float fov, float znear, float zfar);

void pn_calculate_view_projection(mat4 dest);

void pn_free_camera(pn_camera_t* camera);