#pragma once

#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window);
GLFWwindow* createGlfwWindow(int width, int height, const char* title);