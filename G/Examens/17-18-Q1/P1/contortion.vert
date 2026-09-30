#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;
out vec2 vtexCoord;

uniform float time;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    vec3 vtx = vertex;
    if (vertex.y >= 0.5) {
        float phi = (vtx.y - 0.5) * sin(time);
        float c = cos(phi), s = sin(phi);
        vtx = mat3(
            vec3(1, 0, 0),
            vec3(0, c, s),
            vec3(0, -s, c)
        ) * (vtx - vec3(0, 1, 0));
        vtx.y += 1;
    }

    frontColor = vec4(color, 1);
    gl_Position = modelViewProjectionMatrix * vec4(vtx, 1.0);
}
