#include "pn/pn.h"
#include "pn/pn_common.h"

#include "pn_core/pn_core_variables.h"
#include "pn_core/pn_core_init.h"

#include <stdlib.h>
#include <GL/glew.h>

bool pn_init() {
	if(!__pn_core_preinit()) return false;

	__should_run = true;

	return true;
}

bool pn_should_run() {
	return __should_run && !glfwWindowShouldClose(__window_instance->m_glfw_window);
}

void pn_exit() {
	pn_free_window(__window_instance);
	glfwTerminate();
}

void pn_start_frame() {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void pn_end_frame() {
	glfwSwapBuffers(__window_instance->m_glfw_window);
}