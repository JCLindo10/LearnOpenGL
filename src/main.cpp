#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// First thing we wanna draw :)
std::array<double, 9> triangleVertices = {
    -0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
     0.0,  0.5, 0.0
};

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

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;

    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    uint vertexBufferObjectId;
    glGenBuffers(1, &vertexBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices.data(), GL_STATIC_DRAW);

    uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    const size_t infoLogSize = 512;
    char infoLog[infoLogSize];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    uint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, infoLogSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }   

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    uint vertexArrayObjectId;
    glGenVertexArrays(1, &vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObjectId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}