#version 330 core
layout (location = 0) in vec3 aPos; // Position of data pertaining to spatial position
layout (location = 1) in vec3 aColor; // Position of data pertaining to color

out vec3 ourColor; // For the fragment shader

void main () {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor; // Sets ourColor to be the input color from vertex data
}