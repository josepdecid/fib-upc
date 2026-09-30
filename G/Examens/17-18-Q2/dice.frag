#version 330 core

in vec3 V;
in vec3 N;

out vec4 fragColor;

const vec2 first = vec2(0.5, 0.5);
const vec2 center = vec2(0, 0);
const vec2 last = vec2(-0.5, -0.5);
const vec4 black = vec4(0, 0, 0, 1);

const float tol = 0.005;

void main() {
    vec3 NN = abs(normalize(N));
    if (abs(NN.x - 1) < tol) {
        fragColor = distance(V.yz, center) < 0.2 ? black : vec4(1, 0, 0, 1);
    } else if (abs(NN.y - 1) < tol) {
        fragColor = distance(V.xz, first) < 0.2 || distance(V.xz, last) < 0.2
            ? black : vec4(0, 1, 0, 1);
    } else {
        fragColor = distance(V.xy, first) < 0.2 || distance(V.xy, center) < 0.2 || distance(V.xy, last) < 0.2
            ? black : vec4(0, 0, 1, 1);
    }
}

