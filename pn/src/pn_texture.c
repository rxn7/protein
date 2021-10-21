#include "pn_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

pn_texture_t* pn_texture_create(const char* path) {
	pn_texture_t* texture = malloc(sizeof(pn_texture_t));

	stbi_set_flip_vertically_on_load(1);
	u8* buffer = stbi_load(path, &texture->m_width, &texture->m_height, &texture->m_bits_per_pixel, 4);
	
	glGenTextures(1, &texture->m_id);
	glBindTexture(GL_TEXTURE_2D, texture->m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->m_width, texture->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	pn_texture_unbind();

	if(buffer){
		stbi_image_free(buffer);
	}

	return texture;
}

void pn_texture_bind(pn_texture_t* texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->m_id);
}

void pn_texture_unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void pn_texture_free(pn_texture_t* texture) {
	glDeleteTextures(1, &texture->m_id);
	free(texture);
}