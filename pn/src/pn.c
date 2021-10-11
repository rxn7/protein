#include "pn.h"

#include "pn_vars.h"
#include "pn_init.h"

bool pn_should_run() { 
	return pn_should_run && !glfwWindowShouldClose(__pn_window_instance->m_glfw_window);
}

static void pn_update_delta_time() {
	f32 current_frame = glfwGetTime();
	__pn_delta_time = current_frame - __pn_last_frame;
	__pn_last_frame = current_frame;
}

void pn_exit() {
	pn_free_window(__pn_window_instance);
	glfwTerminate();

	pn_free_shader_program(__pn_default_shader_program);
	
    pn_log("Exiting...");
}

void pn_start_frame() {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pn_update_delta_time();
	pn_update_input();
}

void pn_end_frame() {
	glfwSwapBuffers(__pn_window_instance->m_glfw_window);
}
