#include "pn_callbacks.h"


void pn_glfw_error_callback(int error, const char* desc) {
    pn_log("GLFW ERROR %i: %s\n", error, desc);
}

void pn_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
}