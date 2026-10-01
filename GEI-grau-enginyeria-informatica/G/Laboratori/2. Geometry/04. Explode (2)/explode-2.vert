#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 vNormal;
out vec4 vfrontColor;

void main() {
    vNormal = normal;
    vfrontColor = vec4(color, 1);
    gl_Position = vec4(vertex, 1);
}
