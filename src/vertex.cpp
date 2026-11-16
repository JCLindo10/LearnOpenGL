#include "vertex.h"
#include "glad/glad.h"
#include <span>

unsigned int createBuffer() {
    unsigned int bufferId;
    glGenBuffers(1, &bufferId);
    return bufferId;
}

unsigned int createVertexArray() {
    unsigned int vertexArrayObjectId;
    glGenVertexArrays(1, &vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);
    return vertexArrayObjectId;
}

void bindVertices(unsigned int vertexBufferObjectId, unsigned int elementBufferObjectId, 
                  std::span<const float> vertices, std::span<const unsigned int> indices) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
