#version 330 core

in vec3 gnormal;
in vec4 gpos;
out vec4 fragColor;

uniform mat3 normalMatrix;
uniform sampler2D grass_top_0;
uniform sampler2D grass_side_1;

uniform float d;
const vec3 Grey = vec3(0.8);

void main() {
    if (gnormal.z == 0) {
        fragColor = texture(grass_side_1, vec2(
            4 * (gpos.x - gpos.y), gpos.z/d));
    } else {
        fragColor = texture(grass_top_0, 4 * gpos.xy);
    } if (fragColor.a < 0.5) discard;
}
