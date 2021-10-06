#include "pn_input.h"
#include "pn_vars.h"

bool pn_is_key_pressed(pn_key_t key) {
	return glfwGetKey(__pn_window_instance->m_glfw_window, key) == GLFW_PRESS;	
}

void pn_lock_mouse() {
	glfwSetInputMode(__pn_window_instance->m_glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void pn_unlock_mouse() {
	glfwSetInputMode(__pn_window_instance->m_glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}