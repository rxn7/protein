#pragma once

#include "pn.h"

void pn_glfw_error_callback(int error, const char* desc);
void pn_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);