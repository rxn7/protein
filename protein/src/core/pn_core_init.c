#include "core/pn_core_init.h"

#include "pn.h"

#include "core/pn_core_variables.h"
#include "core/callbacks/pn_core_glfw_callbacks.h"


bool __pn_core_preinit() {
	if(__pre_inited) return true;

	// Connect the GLFW callbacks.
	glfwSetErrorCallback(__pn_core_glfw_error_callback);

	// Initialize the GLFW.
	if(glfwInit() != GLFW_TRUE) {
		pn_log("Failed to initialize GLFW!\n");
		return false;
	}
	
	// GLFW Window hints.
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // We will make the window visible at the end of postinit.

	__pre_inited = true;

	return true;
}

bool __pn_core_postinit() {
	// Check if the window instance exists.
	if(__window_instance == NULL){
		pn_log("Failed to post init: Window Instance is NULL!\n");
		__should_run = false;
		return false;

	}
	
	glfwSetKeyCallback(__window_instance->m_glfw_window, __pn_core_glfw_key_callback);

	// Make the context current for the window instance.
	glfwMakeContextCurrent(__window_instance->m_glfw_window);

	// Initialize the GLEW.
	int glew_result = glewInit();
	if(glew_result != GLEW_OK) {
		pn_log("Failed to initialize GLEW: %s\n", glewGetErrorString(glew_result));
		__should_run = false;
		return false;
	}

	// Setting up the OpenGL.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glfwShowWindow(__window_instance->m_glfw_window);

	return true;
}