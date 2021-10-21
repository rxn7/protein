#pragma once

#include "pn_common.h"
#include <GLFW/glfw3.h>

typedef struct {
	GLFWwindow* m_glfw_window;
	u32 m_width, m_height;
	char* m_title;
} pn_window_t;



bool pn_window_create(const char* title, u32 width, u32 height);
void pn_window_update_viewport(void);
void pn_window_set_title(char* title);
void pn_window_set_size(int width, int height);
void pn_window_free(pn_window_t* window);