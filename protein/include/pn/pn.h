#pragma once
#include "pn_common.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct {
	GLFWwindow* m_glfw_window;
	u32 m_width, m_height;
	char* m_title;
} pn_window_t;

pn_window_t* pn_create_window(char* title, u32 width, u32 height);

bool pn_init();