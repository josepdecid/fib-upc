#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec2 vtexCoord;
out vec3 N;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    N = normalMatrix * normal;
    vec4 V = modelViewProjectionMatrix * vec4(vertex, 1);
    vtexCoord = V.xy / V.w;
    gl_Position = V;
}
