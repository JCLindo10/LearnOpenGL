#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <window.h>
#include <shader.h>
#include <vertex.h>
#include <stdexcept>
#include <iostream>

// Display two triangles by adding vertices to the buffer
int exercise1() {
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
    unsigned int elementBufferObjectId = createBuffer();

    std::array<float, 18> vertices = {
        -0.25,  -0.25, 0.0,
        -0.25, 0.25, 0.0,
        0.25, 0.25, 0.0,
        .25,  -.25, 0.0,
        .830, -.75, 0.0,
        .00, -.75, 0.0
    };
    std::array<unsigned int, 6> indices = {
        0, 1, 2,
        3, 4, 5
    };

    bindVertices(vertexBufferObjectId, elementBufferObjectId, vertices, indices);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindVertexArray(vertexArrayObjectId);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;

}

// Display two triangles next to each other with separate VAO and VBO
void exercise2() {
    GLFWwindow *window;
    try {
        window = createGlfwWindow(800, 600, "LearnOpenGLExercises");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    unsigned int leftTriangleVertexBufferObjectId = createBuffer();
    unsigned int leftTriangleElementBufferObjectId = createBuffer();
    unsigned int leftTriangleVertexArrayObjectId = createVertexArray();

    std::array<float, 9> leftTriangleVertices = {
        -0.25,  -0.25, 0.0,
        -0.25, 0.25, 0.0,
        0.25, 0.25, 0.0
    };
    std::array<unsigned int, 3> leftTriangleIndices = {
        0, 1, 2
    };

    bindVertices(leftTriangleVertexBufferObjectId, leftTriangleElementBufferObjectId, leftTriangleVertices, leftTriangleIndices);

    unsigned int rightTriangleVertexBufferObjectId = createBuffer();
    unsigned int rightTriangleElementBufferObjectId = createBuffer();
    unsigned int rightTriangleVertexArrayObjectId = createVertexArray();

    std::array<float, 9> rightTriangleVertices = {
        .25,  -.25, 0.0,
        .830, -.75, 0.0,
        .00, -.75, 0.0
    };

    std::array<unsigned int, 3> rightTriangleIndices = {
        0, 1, 2
    };

    bindVertices(rightTriangleVertexBufferObjectId, rightTriangleElementBufferObjectId, rightTriangleVertices, rightTriangleIndices);

    unsigned int shaderProgramId = getShaderProgram();


    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);

        glBindVertexArray(leftTriangleVertexArrayObjectId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glBindVertexArray(rightTriangleVertexArrayObjectId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

// Create two separate shader programs. One will use a different fragment shader that outputs the color yellow.
// Draw both triangles again, one of them being yellow
void exercise3() {
    
}

int main() {
    (void)exercise1();
    exercise2();
    exercise3();
    return 0;
}