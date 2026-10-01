#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 vtx;

uniform mat4 modelViewProjectionMatrix;

void main() {
    vtx = modelViewProjectionMatrix * vec4(vertex, 1);
    gl_Position = vtx;
}
