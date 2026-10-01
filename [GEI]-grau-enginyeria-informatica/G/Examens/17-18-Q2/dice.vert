#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 V;
out vec3 N;

uniform mat4 modelViewProjectionMatrix;

void main() {
    V = vertex;
    N = normal;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
