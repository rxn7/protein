#pragma once

#include "pn_common.h"

typedef struct {
	u32 m_id;
	u32 m_width, m_height;
	u32 m_bits_per_pixel;
} pn_texture_t;

pn_texture_t* pn_texture_create(const char* path);
void pn_texture_bind(pn_texture_t* texture);
void pn_texture_unbind();
void pn_texture_free(pn_texture_t* texture);