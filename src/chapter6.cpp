#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include "window.h"
#include "shader.h"
#include "vertex.h"
    
void redTriangle() {
    GLFWwindow *window = createGlfwWindow(800, 600, "Chapter 6"); // If this fails, we die anyway

    unsigned int vertexBufferObjectId = createBuffer();
    unsigned int vertexArrayObjectId = createVertexArray();
    unsigned int elementBufferObjectId = createBuffer();

    std::array<float, 9> vertices = {
         0.0, 0.5, 0.0,
         0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    };

    std::array<unsigned int, 3> indices = {
        0, 1, 2,
    };

    bindVertices(vertexBufferObjectId, elementBufferObjectId, vertices, indices);

    unsigned int redShaderId = getShaderProgram("/home/jake/code/learn_opengl/src/color_chooser.vert", "/home/jake/code/learn_opengl/src/color_chooser.frag");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(redShaderId);
        glBindVertexArray(vertexArrayObjectId);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}
    
int main() {
    redTriangle();

    return 0;
}