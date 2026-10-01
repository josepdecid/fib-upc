#version 330 core

layout (location = 0) in vec3 vertex;

out vec3 V;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float time;

void main() {
    float phi = 0.1 * time;
    float c = cos(phi), s = sin(phi);
    vec3 vtx = mat3(
        vec3(c, 0, -s),
        vec3(0, 1, 0),
        vec3(s, 0, c)
    ) * vertex;
    V = (modelViewMatrix * vec4(vtx, 1)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(vtx, 1);
}
