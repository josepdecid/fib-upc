#version 330 core

in vec3 vtx;

out vec4 fragColor;

uniform float slice = 0.05; 
uniform vec3 origin = vec3(0, 0, 0);
uniform vec3 axis = vec3(0, 0, 1);

const vec4 blue = vec4(0, 0, 1, 1);
const vec4 cyan = vec4(0, 1, 1, 1);

void main() {
    vec3 a = normalize(axis);
    vec3 line = origin + a * dot(vtx, a);
    int d = int(length(vtx - line) / slice);
    fragColor = mod(d, 2) == 0 ? blue : cyan;
}
