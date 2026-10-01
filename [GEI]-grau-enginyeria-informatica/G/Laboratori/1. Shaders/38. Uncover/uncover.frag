#version 330 core

in vec4 vtx;
out vec4 fragColor;

uniform float time;

void main() {
    if (vtx.x / vtx.w > time - 1) discard;
    fragColor = vec4(0, 0, 1, 1);
}
