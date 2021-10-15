#pragma once

#include "pn_common.h"

enum {
	UNI_MODEL,
	UNI_VIEW,
	UNI_PROJECTION,
	UNI_COLOR,
	UNI_HAS_TEXTURE,
	UNI_LIGHT_COLOR,
	UNI_LIGHT_POS,
	UNI_CAMERA_POS,
	UNI_USE_LIGHT,
	UNI_COUNT,
};

typedef struct {
	u32 m_id;
	u32 m_vert_shader;
	u32 m_frag_shader;
	u32 m_uniforms[UNI_COUNT];
} pn_shader_program_t;

void pn_init_default_shaders();

pn_shader_program_t* pn_create_shader_program(const char* vert_src, const char* frag_src);
void pn_free_shader_program(pn_shader_program_t* program);

void pn_bind_shader_program(pn_shader_program_t* program);
void pn_unbind_shader_program();