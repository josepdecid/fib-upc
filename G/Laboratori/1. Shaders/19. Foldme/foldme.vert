#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

const vec4 BLUE = vec4(0, 0, 1, 1);

void main() {
    float phi = -time * texCoord.s;
    float c = cos(phi), s = sin(phi);
    mat3 rotate = mat3(
            vec3(c, 0, -s),
            vec3(0, 1, 0),
            vec3(s, 0, c)
        );
    vec3 RV = rotate * vertex;

    frontColor = BLUE;
    gl_Position = modelViewProjectionMatrix * vec4(RV, 1);
}
