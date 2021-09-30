#include "pn.h"

#include "pn_init.h"
#include "pn_vars.h"
#include "pn_callbacks.h"

bool pn_init() {
	if(!pn_preinit()) return false;

	__pn_should_run = true;

	return true;
}

bool pn_preinit() {
	if(__pn_pre_inited) return true;

	// Connect the GLFW callbacks.
	glfwSetErrorCallback(pn_glfw_error_callback);

	// Initialize the GLFW.
	if(glfwInit() != GLFW_TRUE) {
		pn_log("Failed to initialize GLFW!");
		return false;
	}

	pn_log("Successfully initialized GLFW!");
	
	// GLFW Window hints.
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // We will make the window visible at the end of postinit.

	__pn_pre_inited = true;

	return true;
}

bool pn_postinit() {
	// Check if the window instance exists.
	if(!__pn_window_instance){
		pn_log("Failed to post init: Window Instance is 0!");
		
		__pn_should_run = false;
		return false;
	}
	
	glfwSetKeyCallback(__pn_window_instance->m_glfw_window, pn_glfw_key_callback);

	// Make the context current for the window instance.
	glfwMakeContextCurrent(__pn_window_instance->m_glfw_window);

	// Initialize the GLEW.
	int glew_result = glewInit();
	if(glew_result != GLEW_OK) {
		pn_log("Failed to initialize GLEW: %s", glewGetErrorString(glew_result));
		__pn_should_run = false;
		return false;
	}

	// Setting up the OpenGL.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glfwShowWindow(__pn_window_instance->m_glfw_window);

	pn_log("Successfully finished post-init!");

	return true;
}