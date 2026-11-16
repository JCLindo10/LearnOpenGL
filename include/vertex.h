#include <span>

unsigned int createBuffer();
unsigned int createVertexArray();
void bindVertices(unsigned int vertexBufferObjectId, unsigned int elementBufferObjectId, 
                  std::span<const float> vertices, std::span<const unsigned int> indices);