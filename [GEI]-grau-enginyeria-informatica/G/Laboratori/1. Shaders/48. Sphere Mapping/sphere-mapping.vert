#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec3 V;
out vec3 N;
out vec3 O;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;
uniform mat3 normalMatrix;
uniform bool worldSpace;

void main() {
    V = worldSpace ? vertex : (modelViewMatrix * vec4(vertex, 1)).xyz;
    N = worldSpace ? normal : normalMatrix * normal;
    O = worldSpace ? (modelViewMatrixInverse * vec4(0, 0, 0, 1)).xyz : vec3(0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
