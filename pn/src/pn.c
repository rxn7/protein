#include "pn.h"

#include "pn_vars.h"
#include "pn_init.h"

bool pn_should_run(void) { 
	return __pn_should_run && !glfwWindowShouldClose(__pn_window_instance->m_glfw_window);
}

static void pn_update_delta_time(void) {
	f32 current_frame = glfwGetTime();
	__pn_delta_time = current_frame - __pn_last_frame;
	__pn_last_frame = current_frame;
}

void pn_exit(void) {
	pn_window_free(__pn_window_instance);
	glfwTerminate();

	pn_shader_program_free(__pn_default_shader_program);
	
    pn_log("Exiting...");
}

void pn_start_frame(void) {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pn_update_delta_time();
	pn_input_update();
}

void pn_end_frame(void) {
	glfwSwapBuffers(__pn_window_instance->m_glfw_window);
}
