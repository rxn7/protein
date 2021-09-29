#include "pn_input.h"
#include "core/pn_core_variables.h"

bool pn_is_key_pressed(pn_key_t key) {
	return glfwGetKey(__window_instance->m_glfw_window, key) == GLFW_PRESS;	
}