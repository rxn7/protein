#pragma once

#include "pn_common.h"

typedef struct {
	vec3 m_pos;
	vec3 m_rot;
	vec3 m_scale;
} pn_transform_t;

void pn_calculate_transform_model(pn_transform_t* transform, mat4 dest);
void pn_init_transform(pn_transform_t* transform);