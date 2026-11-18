#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int getShaderProgram();
unsigned int getShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath);