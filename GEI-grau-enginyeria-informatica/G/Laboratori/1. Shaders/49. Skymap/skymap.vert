#version 330 core

layout (location = 0) in vec3 vertex;

out vec3 vtx;
out vec3 obs;

uniform mat4 modelViewMatrixInverse;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    vtx = vertex;
    obs = (modelViewMatrixInverse * vec4(0, 0, 0, 1)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
