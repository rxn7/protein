#include "pn_callbacks.h"
#include "pn_log.h"
#include "pn_vars.h"

void pn_glfw_error_callback(int error, const char* desc) {
    pn_log("GLFW ERROR %i: %s\n", error, desc);
}

void pn_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
}

void pn_glfw_resize_callback(GLFWwindow* window, int width, int height) {
    __pn_window_instance->m_width = width;
    __pn_window_instance->m_height = height;
    pn_update_viewport();
}