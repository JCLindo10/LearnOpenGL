#version 330 core
layout (location = 0) in vec3 aPos; // Position has attribute position 0

out vec4 vertexColor; // This will be an input to the fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0); // A vec3 as input to a vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // Red
}