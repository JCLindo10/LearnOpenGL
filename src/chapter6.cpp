#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include "window.h"
#include "shader.h"
#include "vertex.h"
#include <cmath>
    
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

    unsigned int redShaderId = getShaderProgram("/home/jake/code/learn_opengl/src/shaders/color_chooser.vert", "/home/jake/code/learn_opengl/src/shaders/color_chooser.frag");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(redShaderId);
        glBindVertexArray(vertexArrayObjectId);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}

void transformColorWithTime(GLenum shaderProgramId, float speed) {
    float currentTime = glfwGetTime();
    float greenValue = (sin(currentTime) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgramId, "ourColor");
    glUseProgram(shaderProgramId);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

void uniform() {
    GLFWwindow *window = createGlfwWindow(800, 600, "Uniform");

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

    unsigned int redShaderId = getShaderProgram("/home/jake/code/learn_opengl/src/shaders/color_chooser.vert", "/home/jake/code/learn_opengl/src/shaders/uniform.frag");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(redShaderId);

        transformColorWithTime(redShaderId, 1.0f);

        glBindVertexArray(vertexArrayObjectId);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}

void colorPerVertex() {
    GLFWwindow *window = createGlfwWindow(800, 600, "per-vertex");

    unsigned int vertexBufferObjectId = createBuffer();
    unsigned int vertexArrayObjectId = createVertexArray();
    unsigned int elementBufferObjectId = createBuffer();

    std::array<float, 18> vertices = {
         0.0, 0.5, 0.0, 1.0, 0.0, 0.0,
         0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
        -0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
    };

    std::array<unsigned int, 3> indices = {
        0, 1, 2,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int shaderProgramId = getShaderProgram("/home/jake/code/learn_opengl/src/shaders/per_vertex.vert", "/home/jake/code/learn_opengl/src/shaders/per_vertex.frag");

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);

        glBindVertexArray(vertexArrayObjectId);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}

void translateVerticesRight(GLenum shaderProgramId, float amount) {
    int positionTransformLocation = glGetUniformLocation(shaderProgramId, "positionOffset");

    if (positionTransformLocation == -1) { // Uniform DNE
        return;
    }

    glUseProgram(shaderProgramId);
    glUniform3f(positionTransformLocation, amount, 0.0, 0.0f);
}

void exercises(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
    GLFWwindow *window = createGlfwWindow(800, 600, "Exercise 1");

    unsigned int vertexBufferObjectId = createBuffer();
    unsigned int vertexArrayObjectId = createVertexArray();
    unsigned int elementBufferObjectId = createBuffer();

    std::array<float, 18> vertices = {
         0.0, 0.5, 0.0, 1.0, 0.0, 0.0,
         0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
        -0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
    };

    std::array<unsigned int, 3> indices = {
        0, 1, 2,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int shaderProgramId = getShaderProgram(vertexShaderPath, fragmentShaderPath);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        translateVerticesRight(shaderProgramId, 0.50);

        glBindVertexArray(vertexArrayObjectId);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}
    
int main() {
    redTriangle();
    uniform();
    colorPerVertex();

    exercises("/home/jake/code/learn_opengl/src/shaders/chapter6_1.vert", "/home/jake/code/learn_opengl/src/shaders/chapter6_1.frag");
    exercises("/home/jake/code/learn_opengl/src/shaders/chapter6_2.vert", "/home/jake/code/learn_opengl/src/shaders/chapter6_2.frag");
    exercises("/home/jake/code/learn_opengl/src/shaders/chapter6_3.vert", "/home/jake/code/learn_opengl/src/shaders/chapter6_3.frag");

    return 0;
}