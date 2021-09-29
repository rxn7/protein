#include "pn_window.h"
#include "core/pn_core_variables.h"
#include "core/pn_core_init.h"

#include <stdlib.h>

pn_window_t* pn_create_window(char* title, u32 width, u32 height) {
	pn_window_t* window = malloc(sizeof(pn_window_t));
	window->m_title = title;
	window->m_width = width;
	window->m_height = height;
	window->m_glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if(window->m_glfw_window == NULL){
		pn_log("Failed to create window!");	
		return NULL;
	}

	__window_instance = window;

	__pn_core_postinit(); 

	return window;
}

void pn_set_window_title(char* title) {
	if(__window_instance == 0){
		pn_log("Failed to set window title: the window instance is 0!");
		__should_run = false; // We shouldn't continue the program if the window instance doesnt exist.
		return;
	}

	__window_instance->m_title = title;
	glfwSetWindowTitle(__window_instance->m_glfw_window, title);
}

void pn_set_window_size(int width, int height) {
	if(width < 100) width = 100;
	if(height < 100) height = 100;

	__window_instance->m_width = width;
	__window_instance->m_height = height;

	glfwSetWindowSize(__window_instance->m_glfw_window, width, height);
}

void pn_free_window(pn_window_t* window) {
	if(window != NULL) free(window);
}
