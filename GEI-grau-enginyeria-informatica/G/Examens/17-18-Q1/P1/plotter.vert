#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;

uniform float xmin = -6;
uniform float xmax = 6;
uniform float ymin = -2;
uniform float ymax = 2;

float mapTo(float value, float il, float iu, float ol, float ou) {
    return (value - il) * (ou - ol) / (iu - il) + ol;
}

void main() {
    float X = mapTo(vertex.x, -1, 1, xmin, xmax);
    float Y;
    if (vertex.z == -2) {
        Y = sin(X);
        frontColor = vec4(1, 0, 0, 1);
    } else if (vertex.z == 0) {
        Y = 2 * exp(-X*X/6);
        frontColor = vec4(0, 1, 0, 1);
    } else {
        Y = sin(2*X);
        frontColor = vec4(0, 0, 1, 1);
    }
    Y = mapTo(Y, ymin, ymax, -1, 1);
    gl_Position = vec4(vertex.x, vertex.y + Y, 0, 1);
}
