#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 vfrontColor;

void main() {
    gl_Position = vec4(vertex, 1);
}
