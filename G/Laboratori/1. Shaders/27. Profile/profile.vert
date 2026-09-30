#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;
out vec3 V;
out vec3 N;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    V = (modelViewMatrix * vec4(vertex, 1)).xyz;
    N = normalize(normalMatrix * normal);
    frontColor = vec4(color, 1) * N.z;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
