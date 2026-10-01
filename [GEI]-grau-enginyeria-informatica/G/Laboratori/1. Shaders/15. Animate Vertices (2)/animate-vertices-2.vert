#version 330 core

# define TAU 6.2831853071795865

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed = 0.1;
uniform float time;
uniform float amplitude = 0.1;
uniform float freq = 1;

void main() {
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
    vec3 vtx = vertex + amplitude * sin(TAU * (freq * time + texCoord.s)) * normal;
    gl_Position = modelViewProjectionMatrix * vec4(vtx, 1.0);
}
