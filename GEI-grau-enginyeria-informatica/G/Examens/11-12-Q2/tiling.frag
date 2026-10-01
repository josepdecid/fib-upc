#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D T;

void main() {
    fragColor = texture(T, vtexCoord);
}
