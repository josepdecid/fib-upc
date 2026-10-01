#version 330 core

in vec2 vtexCoord;
in vec3 N;

out vec4 fragColor;

uniform sampler2D sampler;

void main() {
    fragColor = texture(sampler, vtexCoord) * normalize(N).z;
}
