#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 NE;
out vec3 P;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    NE = normalMatrix * normal;
    P = (modelViewMatrix * vec4(vertex, 1)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
