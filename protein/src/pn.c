#include "pn/pn.h"
#include "pn_core/pn_core_variables.h"
#include <stdlib.h>

pn_window_t* pn_create_window(char* title, u32 width, u32 height){
	pn_window_t* window = malloc(sizeof(pn_window_t));
	window->m_title = title;
	window->m_width = width;
	window->m_height = height;
	window->m_glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

	__window_instance = window;	
	glfwMakeContextCurrent(window->m_glfw_window);

	return window;
}

bool pn_init(){
	if(!glfwInit()) return false;

	return true;
}