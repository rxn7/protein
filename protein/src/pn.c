#include "pn.h"
#include "pn_common.h"

#include "pn_vars.h"
#include "pn_init.h"

#include <stdlib.h>
#include <GL/glew.h>

bool pn_should_run() { 
	return __pn_should_run && !glfwWindowShouldClose(__pn_window_instance->m_glfw_window);
}

void pn_exit() {
	pn_free_window(__pn_window_instance);
	glfwTerminate();    
}

void pn_start_frame() {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void pn_end_frame() {
	glfwSwapBuffers(__pn_window_instance->m_glfw_window);
}

void pn_set_clear_color(pn_color_t color){
	glClearColor(PN_RGBA_F32(color));
}