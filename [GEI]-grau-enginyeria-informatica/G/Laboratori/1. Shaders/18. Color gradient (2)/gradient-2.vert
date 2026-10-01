#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

const vec4 RED = vec4(1, 0, 0, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);
const vec4 GREEN = vec4(0, 1, 0, 1);
const vec4 CIAN = vec4(0, 1, 1, 1);
const vec4 BLUE = vec4(0, 0, 1, 1);

float scaleVert(float y, float lower, float upper) {
    return (y - lower) / (upper  - lower);
}

vec4 getFrontColor(float height) {
    if (height < -0.5)
        return mix(RED, YELLOW, scaleVert(height, -1.0, -0.5));
    else if (height < 0.0)
        return mix(YELLOW, GREEN, scaleVert(height, -0.5, 0.0));
    else if (height < 0.5)
        return mix(GREEN, CIAN, scaleVert(height, 0.0, 0.5));
    else
        return mix(CIAN, BLUE, scaleVert(height, 0.5, 1.0));
}

void main() {
    vec4 vtx = modelViewProjectionMatrix * vec4(vertex, 1);
    frontColor = getFrontColor(vtx.y / vtx.w);
    gl_Position = vtx;
}
