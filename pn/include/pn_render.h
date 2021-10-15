#pragma once

#include "pn_color.h"
#include "pn_common.h"
#include "pn_shader.h"
#include "pn_transform.h"
#include "pn_texture.h"
#include "pn_math.h"

typedef enum {
	PN_TRIANGLE,
	PN_QUAD,
	PN_PYRAMID,
	PN_CUBE,
} pn_primite_t;

typedef struct {
	v3 m_pos;
    v3 m_normal;
	v2 m_uv;
} pn_vertex_t;

typedef struct {
	pn_transform_t m_transform;
	u32 m_vao;
	u32 m_vbo;
	u32 m_ebo;

    u32 m_vertex_count;

	bool m_use_light;

	pn_color_t m_color;
} pn_render_object_t;


pn_render_object_t* pn_create_render_object(pn_vertex_t* vertices, u32 vertex_count);
pn_render_object_t* pn_create_primitive_render_object(pn_primite_t type);

void pn_render_render_object(pn_render_object_t* render_object, pn_shader_program_t* shader_program, pn_texture_t* texture);

void pn_free_render_object(pn_render_object_t* render_object);

void pn_set_clear_color(pn_color_t color);

void pnm_set_light_color(pn_color_t color);

void pn_set_light_pos(v3 pos);