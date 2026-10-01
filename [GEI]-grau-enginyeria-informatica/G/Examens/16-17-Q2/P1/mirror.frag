#version 330 core

in vec2 vtexCoord;

out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;

void main() {
    vec2 coords = vtexCoord;
    if (fract(time) < 0.5) {
        if (coords.t > 0.5) coords.t = -coords.t;
    } else if (coords.t < 0.5) coords.t= -coords.t;
    fragColor = texture(colorMap, coords);
}
