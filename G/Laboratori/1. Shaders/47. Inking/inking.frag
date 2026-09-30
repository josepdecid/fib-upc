#version 330 core

in vec2 vtexCoord;

out vec4 fragColor;

uniform sampler2D texture0;
uniform int textureSize = 1024; 
uniform int edgeSize = 2; 
uniform float threshold = 0.2;

void main() {
    vec2 left = vtexCoord + edgeSize * vec2(-1, 0) / textureSize;
    vec2 right = vtexCoord + edgeSize * vec2(1, 0) / textureSize;
    vec2 bottom = vtexCoord + edgeSize * vec2(0, -1) / textureSize;
    vec2 top = vtexCoord + edgeSize * vec2(0, 1) / textureSize;

    float GX = length(texture(texture0, right) - texture(texture0, left));
    float GY = length(texture(texture0, top) - texture(texture0, bottom));
    vec2 G = vec2(GX, GY);

    fragColor = length(G) > threshold
        ? vec4(0, 0, 0, 1) : texture(texture0, vtexCoord);
}
