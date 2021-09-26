#include "pn_core/pn_core_init.h"
#include "pn/pn.h"
#include "pn_core/pn_core_variables.h"
#include  <stdio.h>

bool __pn_core_preinit() {
	if(__pre_inited) return true;

	if(!glfwInit()) {
		printf("Error initializing glfw\n");
		return false;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	__pre_inited = true;

	return true;
}

bool __pn_core_postinit() {
	int glew_result = glewInit();
	if(glew_result != GLEW_OK) {
		printf("Error initializing glew: %s\n", glewGetErrorString(glew_result));
		return false;
	}

	glfwMakeContextCurrent(__window_instance->m_glfw_window);
	
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

	return true;
}