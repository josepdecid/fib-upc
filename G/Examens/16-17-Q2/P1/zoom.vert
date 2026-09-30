#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform float time;

void main() {
    vec3 N = normalize(normalMatrix * normal);
    float a = 0.25 * distance(boundingBoxMax, boundingBoxMin);
    vec4 vtx = modelViewMatrix * vec4(vertex, 1);
    vtx.z += a * sin(time);

    frontColor = vec4(color,1.0) * N.z;
    gl_Position = projectionMatrix * vtx;
}
