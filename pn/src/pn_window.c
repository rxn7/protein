#include "pn_window.h"
#include "pn_vars.h"
#include "pn_init.h"
#include "pn_log.h"

#include <stdlib.h>

pn_window_t* pn_create_window(char* title, u32 width, u32 height) {
	pn_window_t* window = malloc(sizeof(pn_window_t));
	window->m_title = title;
	window->m_width = width;
	window->m_height = height;
	window->m_glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if(window->m_glfw_window == NULL){
		pn_error("Failed to create window!");	
		return NULL;
	}

	__pn_window_instance = window;

	pn_postinit(); 

	return window;
}

void pn_set_window_title(char* title) {
	if(__pn_window_instance == 0){
		pn_error("Failed to set window title: the window instance is 0!");
		__pn_should_run = false; // We shouldn't continue the program if the window instance doesnt exist.
		return;
	}

	__pn_window_instance->m_title = title;
	glfwSetWindowTitle(__pn_window_instance->m_glfw_window, title);
}

void pn_set_window_size(int width, int height) {
	if(width < 100) width = 100;
	if(height < 100) height = 100;

	__pn_window_instance->m_width = width;
	__pn_window_instance->m_height = height;

	glfwSetWindowSize(__pn_window_instance->m_glfw_window, width, height);
}

void pn_update_viewport() {
	int w = __pn_window_instance->m_width;
	int h = __pn_window_instance->m_height;
	f32 aspect = (f32)w / (f32)h;

	glViewport(0, 0, w, h);
}

void pn_free_window(pn_window_t* window) {
	if(window != NULL) free(window);
}
