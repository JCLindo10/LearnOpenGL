#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // Input from color_chooser.vert

void main() {
    FragColor = vertexColor;
}