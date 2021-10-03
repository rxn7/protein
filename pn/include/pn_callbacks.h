#pragma once

#include "pn_common.h"

void pn_glfw_error_callback(int error, const char* desc);
void pn_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void pn_glfw_resize_callback(GLFWwindow* window, int width, int height);