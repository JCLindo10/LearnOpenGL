#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include "window.h"
#include "shader.h"
    
static const size_t INFO_LOG_SIZE = 512;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// First thing we wanna draw :)
// std::array<float, 9> vertices = {
//     -0.5, -0.5, 0.0,
//      0.5, -0.5, 0.0,
//      0.0,  0.5, 0.0
// };

std::array<float, 12> vertices = {
     0.5,  0.5, 0.0,
     0.5, -0.5, 0.0,
    -0.5, -0.5, 0.0,
    -0.5,  0.5, 0.0
};

std::array<unsigned int, 6> indices = {
    0, 1, 3,
    1, 2, 3
};

unsigned int getVertexBufferObject() {
    unsigned int vertexBufferObjectId;
    glGenBuffers(1, &vertexBufferObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    return vertexBufferObjectId;
}

unsigned int getElementBufferObject() {
    unsigned int elementBufferObjectId;
    glGenBuffers(1, &elementBufferObjectId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    return elementBufferObjectId;
}

unsigned int getVertexArrayObject() {
    unsigned int vertexArrayObjectId;
    glGenVertexArrays(1, &vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);
    return vertexArrayObjectId;
}

void bindVertices(unsigned int vertexBufferObjectId) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void bindVertices(unsigned int vertexBufferObjectId, unsigned int elementBufferObjectId) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

int main() {
    GLFWwindow *window;
    try {
        window = createGlfwWindow(800, 600, "LearnOpenGL");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    unsigned int vertexBufferObjectId = getVertexBufferObject();
    unsigned int shaderProgramId = getShaderProgram();
    unsigned int vertexArrayObjectId = getVertexArrayObject();
    unsigned int elementBufferObjectId = getElementBufferObject();

    // bindVertices(vertexBufferObjectId);
    bindVertices(vertexBufferObjectId, elementBufferObjectId);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindVertexArray(vertexArrayObjectId);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}