#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform int tiles = 1;

void main() {
    vtexCoord = texCoord * tiles;
    vtexCoord.s = (vtexCoord.s + floor(time * 30))/44;
    gl_Position = vec4(vertex, 1.0);
}
