#include "pn_init.h"
#include "pn_vars.h"
#include "pn_callbacks.h"
#include "pn_common.h"
#include "pn_log.h"
#include "pn_math.h"
#include "pn_camera.h"
#include "pn_shader.h"
#include <cglm/cglm.h>

bool pn_init() {
	if(!pn_preinit()) return false;

	__pn_should_run = true;

	return true;
}

bool pn_preinit() {
	if(__pn_pre_inited) return true;

	glfwSetErrorCallback(pn_glfw_error_callback);

	// Initialize the GLFW.
	if(glfwInit() != GLFW_TRUE) {
		pn_error("Failed to initialize GLFW!");
		return false;
	}

	pn_log("Successfully initialized GLFW!");
	
	// GLFW Window hints.
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // We will make the window visible at the end of postinit.

	__pn_pre_inited = true;

	return true;
}

bool pn_postinit() {
	// Check if the window instance exists.
	if(!__pn_window_instance){
		pn_error("Failed to post init: Window Instance is 0!");
		
		__pn_should_run = false;
		return false;
	}

	// Set the GLFW Callbacks.
	glfwSetFramebufferSizeCallback(__pn_window_instance->m_glfw_window, pn_glfw_resize_callback);
	glfwSetKeyCallback(__pn_window_instance->m_glfw_window, pn_glfw_key_callback);

	// Make the context current for the window instance.
	glfwMakeContextCurrent(__pn_window_instance->m_glfw_window);

	// Initialize the GLEW.
	int glew_result = glewInit();
	if(glew_result != GLEW_OK) {
		pn_error("Failed to initialize GLEW: %s", glewGetErrorString(glew_result));
		__pn_should_run = false;
		return false;
	}

	// OpenGL Settings.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);

	pn_create_camera((vec3){0, 0, -3.f}, 70, 0.01f, 1000.0f);
	pn_update_viewport();

	pn_init_default_shaders();
	glfwShowWindow(__pn_window_instance->m_glfw_window);

	pn_log("Successfully finished post-init!");

	return true;
}