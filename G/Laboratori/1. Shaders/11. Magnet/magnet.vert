#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform float n = 4;
uniform vec4 lightPosition;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;
uniform mat3 normalMatrix;

void main() {
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);

    vec3 F = (modelViewMatrixInverse * lightPosition).xyz;
    float d = distance(F, vertex);
    float w = clamp(1/pow(d, n), 0.0, 1.0);
    vec3 V = (1.0 - w) * vertex + w * F;

    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}
