#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <window.h>
#include <shader.h>
#include <vertex.h>
#include <stdexcept>
#include <iostream>

int main() {
    GLFWwindow *window;
    try {
        window = createGlfwWindow(800, 600, "LearnOpenGLExercises");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    unsigned int vertexBufferObjectId = createBuffer();
    unsigned int shaderProgramId = getShaderProgram();
    unsigned int vertexArrayObjectId = createVertexArray();

    std::array<float, 9> vertices = {
        0.5,  0.5, 0.0,
        0.5, -0.5, 0.0,
        -1.5, -0.5, 0.0
    };
    std::array<unsigned int, 3> indices = {
        0, 1, 2
    };

    bindVertices(vertexBufferObjectId, vertexArrayObjectId, vertices, indices);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindVertexArray(vertexArrayObjectId);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}