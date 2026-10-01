#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;
uniform float time;

const float slice = 30;

vec2 calcRowCol() {
    return vec2(
        floor(time*slice),
        5 - floor(time*slice / 8)
    );
}

void main() {
    vec2 offset = calcRowCol();

    vec4 color = texture(explosion, vec2(
        (vtexCoord.s + offset.s)/8,
        (vtexCoord.t + offset.t)/6
    ));

    fragColor = color * color.a;
}
