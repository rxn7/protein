#pragma once

#include "pn_color.h"
#include "pn_common.h"
#include "pn_shader.h"
#include "pn_transform.h"

typedef struct {
	vec3 m_pos;
	//vec2 m_uv;
} pn_vertex_t;

typedef struct {
	pn_transform_t m_transform;
	u32 m_vao;
	u32 m_vbo;
	u32 m_vertex_count;
} pn_render_object_t;

pn_render_object_t* pn_create_render_object(pn_vertex_t* vertices, u32 vertex_count);
void pn_render_render_object(pn_render_object_t* render_object, pn_shader_program_t* shader_program);
// Note: This function doesn't free vertex array if you allocated it on the heap.
void pn_free_render_object(pn_render_object_t* render_object);

void pn_set_clear_color(pn_color_t color);