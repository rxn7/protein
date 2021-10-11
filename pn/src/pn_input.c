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

void pn_enable_mouse_camera_movement() {
	__pn_camera_mouse_movement = true;
}

void pn_disable_mouse_camera_movement() {
	__pn_camera_mouse_movement = false;
}

void pn_update_input() {
	f64 mouse_x, mouse_y;
	glfwGetCursorPos(__pn_window_instance->m_glfw_window, &mouse_x, &mouse_y);

	if(__pn_camera_mouse_movement && __pn_mouse_x != 0 && __pn_mouse_y != 0) {
		f32 offset_x = mouse_x - __pn_mouse_x;
		f32 offset_y = __pn_mouse_y - mouse_y;
		pn_rotate_camera(offset_x * __pn_mouse_sens, offset_y * __pn_mouse_sens);
	}

	__pn_mouse_x = mouse_x;
	__pn_mouse_y = mouse_y;
}

void pn_set_mouse_sens(f32 sens) {
	__pn_mouse_sens = sens;
}
