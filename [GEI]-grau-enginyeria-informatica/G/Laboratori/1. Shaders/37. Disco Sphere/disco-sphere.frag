#version 330 core

in vec3 V;

out vec4 fragColor;

uniform sampler2D sampler;

void main() {
    vec3 N = normalize(cross(dFdx(V), dFdy(V)));
    vec4 texel = texture(sampler, vec2(N.x, N.y));
    fragColor = texel * N.z;
}
