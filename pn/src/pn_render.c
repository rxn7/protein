#include "pn_render.h"

void pn_set_clear_color(pn_color_t color) {
	glClearColor(PN_RGBA_F32(color));
}