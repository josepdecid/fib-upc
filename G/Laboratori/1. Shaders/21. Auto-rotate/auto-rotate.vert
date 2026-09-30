#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

uniform float speed = 0.5;

void main() {
    vec3 N = normalize(normalMatrix * normal);
    float phi = speed * time;
    float c = cos(phi), s = sin(phi);
    vec3 vtx = mat3(
        vec3(c, 0, -s),
        vec3(0, 1, 0),
        vec3(s, 0, c)
    ) * vertex;

    frontColor = vec4(color, 1);
    gl_Position = modelViewProjectionMatrix * vec4(vtx, 1);
}
