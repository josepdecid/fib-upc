#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

const vec4 RED = vec4(1, 0, 0, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);
const vec4 GREEN = vec4(0, 1, 0, 1);
const vec4 CIAN = vec4(0, 1, 1, 1);
const vec4 BLUE = vec4(0, 0, 1, 1);

float scaleVert(float y, float lower, float upper) {
    return (y - lower) / (upper  - lower);
}

vec4 getFrontColor(float height) {
    if (height < 0.25)
        return mix(RED, YELLOW, scaleVert(height, 0.00, 0.25));
    else if (height < 0.5)
        return mix(YELLOW, GREEN, scaleVert(height, 0.25, 0.50));
    else if (height < 0.75)
        return mix(GREEN, CIAN, scaleVert(height, 0.50, 0.75));
    else
        return mix(CIAN, BLUE, scaleVert(height, 0.75, 1.00));
}

void main() {
    float height = scaleVert(vertex.y, boundingBoxMin.y, boundingBoxMax.y);
    frontColor = getFrontColor(height);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);
}
