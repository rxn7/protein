#pragma once

#include "pn/pn.h"

void __pn_core_glfw_error_callback(int error, const char* desc);
void __pn_core_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);