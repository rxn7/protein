#pragma once

#include "pn_common.h"

typedef struct {
	vec3 m_pos;
	vec3 m_rot;
	vec3 m_scale;
} pn_transform_t;

void pn_transform_get_model(pn_transform_t* transform, mat4 dest);
void pn_transform_init(pn_transform_t* transform);