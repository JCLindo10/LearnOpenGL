#version 330 core
layout (location = 0) in vec3 aPos; // Position of data pertaining to spatial position

uniform vec3 positionOffset;

out vec3 ourPosition;

void main () {
    ourPosition = vec3(aPos + positionOffset);
    gl_Position = vec4(ourPosition, 1.0);
}