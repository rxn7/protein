#pragma once

#include "pn_common.h"

typedef struct {
	GLFWwindow* m_glfw_window;
	u32 m_width, m_height;
	char* m_title;
} pn_window_t;



pn_window_t* pn_create_window(char* title, u32 width, u32 height);

void pn_set_window_title(char* title);

void pn_set_window_size(int width, int height);

void pn_free_window(pn_window_t* window);