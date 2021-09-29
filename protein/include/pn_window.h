#pragma once

#include "pn_common.h"

/*
	This structs holds window data.

	m_title - Window's title.
	m_width - Window's width.
	m_height - Window's height.
	m_glfw_window - Pointer to the GLFWwindow instance.
*/
typedef struct {
	GLFWwindow* m_glfw_window;
	u32 m_width, m_height;
	char* m_title;
} pn_window_t;


/*
	This function creates a window with specified parameters.
*/
pn_window_t* pn_create_window(char* title, u32 width, u32 height);

/*
	This function sets window instance's title to the specified one.
*/
void pn_set_window_title(char* title);

/*
	This function sets window instance's width and height to the specified.
*/
void pn_set_window_size(int width, int height);

/*
	It's not necessary to call this function because pn_exit frees the window instance for you.

	window - Pointer to the window you want to free.
*/
void pn_free_window(pn_window_t* window);