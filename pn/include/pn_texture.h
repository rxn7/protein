#pragma once

#include "pn_common.h"

typedef struct {
	u32 m_id;
	u32 m_width, m_height;
	u32 m_bits_per_pixel;
} pn_texture_t;

pn_texture_t* pn_create_texture(const char* path);
void pn_bind_texture(pn_texture_t* texture);
void pn_unbind_texture();
void pn_free_texture(pn_texture_t* texture);