#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec4 V;
out vec3 NE;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    V = vec4(vertex, 1);
    vtexCoord = texCoord;
    NE = normalMatrix * normal;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
