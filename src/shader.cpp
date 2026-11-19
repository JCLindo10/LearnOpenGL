#include "shader.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

static const int INFO_LOG_SIZE = 512;

void compileShader(unsigned int shaderId, const char* shaderSourceCode, const GLenum shaderType) {
    glShaderSource(shaderId, 1, &shaderSourceCode, NULL);
    glCompileShader(shaderId);

    int success;
    char infoLog[INFO_LOG_SIZE];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Shader compilation failed");
    }
}

unsigned int getShaderProgram() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShader, vertexShaderSource, GL_VERTEX_SHADER);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShader, fragmentShaderSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShader);
    glAttachShader(shaderProgramId, fragmentShader);
    glLinkProgram(shaderProgramId);

    int success;
    char infoLog[INFO_LOG_SIZE];
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramId, INFO_LOG_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        exit(-1);
    }   

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgramId;
}

unsigned int linkShaderProgram(const std::initializer_list<unsigned int> shaderIds) {

    unsigned int shaderProgramId = glCreateProgram();
    for (auto shaderId : shaderIds) {
        glAttachShader(shaderProgramId, shaderId);
    }

    glLinkProgram(shaderProgramId);

    int success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
        std::string errorMsg = "Couldn't link shaders:\n   " + std::string(infoLog);
        throw std::runtime_error(errorMsg);
    }

    return shaderProgramId;
}

std::string getSource(const std::string &filepath) {

    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file" + filepath);
    }

    std::string sourceCode = "";
    std::string line;
    while (std::getline(file, line)) {
        sourceCode.append(line);
        sourceCode.append("\n");
    }

    return sourceCode;

}

unsigned int getShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
    // Not being able to compile/link shaders would be fatal anyway, just let it die

    std::string vertexSource = getSource(vertexShaderPath);
    std::string fragmentSource = getSource(fragmentShaderPath);

    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(vertexShaderId, vertexSource.c_str(), GL_VERTEX_SHADER);
    compileShader(fragmentShaderId, fragmentSource.c_str(), GL_FRAGMENT_SHADER);

    return linkShaderProgram({vertexShaderId, fragmentShaderId});
}