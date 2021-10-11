#include "pn_init.h"
#include "pn_vars.h"
#include "pn_window.h"
#include "pn_callbacks.h"
#include "pn_common.h"
#include "pn_log.h"
#include "pn_math.h"
#include "pn_camera.h"
#include "pn_shader.h"
#include <cglm/cglm.h>

static void pn_set_glfw_hints() {
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // We will make the window visible at the end of postinit.
}

static void pn_set_glfw_callbacks() {
	glfwSetFramebufferSizeCallback(__pn_window_instance->m_glfw_window, pn_glfw_resize_callback);
	glfwSetKeyCallback(__pn_window_instance->m_glfw_window, pn_glfw_key_callback);
}

static bool pn_init_glew() {
	int result = glewInit();
	if(result != GLEW_OK) {
		pn_error("Failed to initialize GLEW: %s", glewGetErrorString(result));
		__pn_should_run = false;
		return false;
	}

	pn_log("Successfully initialized GLEW!");
	return true;
}

static bool pn_init_glfw() {
	glfwSetErrorCallback(pn_glfw_error_callback);

	if(glfwInit() != GLFW_TRUE) {
		pn_error("Failed to initialize GLFW!");
		return false;
	}

	pn_log("Successfully initialized GLFW!");
	return true;
}

static void pn_init_opengl() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	pn_log("Successfully initialized OpenGL!");
}

static bool pn_pre_init() {
	if(__pn_pre_inited) return true;

	if(!pn_init_glfw()) return false;
	pn_set_glfw_hints();

	__pn_camera_update_queued = true;
	__pn_pre_inited = true;

	pn_log("Successfully done pre_init!");
	return true;
}

static bool pn_post_init() {
	if(!__pn_window_instance){
		pn_error("Failed to do post_init: Window Instance is 0!");
		__pn_should_run = false;
		return false;
	}

	glfwMakeContextCurrent(__pn_window_instance->m_glfw_window);
	pn_set_glfw_callbacks();
	if(glfwRawMouseMotionSupported()) glfwSetInputMode(__pn_window_instance->m_glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	if(!pn_init_glew())   return false;
 	pn_init_opengl();

	// Enable raw mouse motion if supported.
	if(glfwRawMouseMotionSupported()) glfwSetInputMode(__pn_window_instance->m_glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	pn_create_camera((vec3){0, 0, -3.f}, 70, 0.01f, 1000.0f);
	pn_update_viewport();

	pn_init_default_shaders();

	glfwShowWindow(__pn_window_instance->m_glfw_window);

	pn_log("Successfully done post_init!");

	return true;
}

bool pn_init(const char* title, u32 width, u32 height) {
	if(!pn_pre_init()) 							return false;
	if(!pn_create_window(title, width, height)) return false;
	if(!pn_post_init()) 							return false;

	__pn_should_run = true;
	return true;
}
