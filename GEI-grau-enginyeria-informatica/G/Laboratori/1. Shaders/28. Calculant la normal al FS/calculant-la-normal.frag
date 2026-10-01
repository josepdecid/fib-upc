#version 330 core

in vec3 frontColor;
in vec3 vtx;

out vec4 fragColor;

void main() {
    vec3 N = normalize(cross(dFdx(vtx), dFdy(vtx)));
    fragColor = vec4(frontColor, 1) * N.z;
}
