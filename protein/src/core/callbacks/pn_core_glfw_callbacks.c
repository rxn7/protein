#include "pn_core/callbacks/pn_core_glfw_callbacks.h"

void __pn_core_glfw_error_callback(int error, const char* desc) {
    pn_log("GLFW ERROR %i: %s\n", error, desc);
}

void __pn_core_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    pn_log("Key pressed: %i\n", key);
}