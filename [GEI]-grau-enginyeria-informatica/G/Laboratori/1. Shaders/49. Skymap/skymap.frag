#version 330 core

in vec3 vtx;
in vec3 obs;

out vec4 fragColor;

uniform sampler2D texture0;

vec4 sphereMap(sampler2D tex, vec3 V) { 
    float z = sqrt((V.z + 1)/2);
    vec2 st = vec2(
       (V.x/(2*z) + 1)/2,
       (V.y/(2*z) + 1)/2
    );
    return texture(tex, st);
} 

void main() {
    vec3 V = normalize(vtx - obs);
    fragColor = sphereMap(texture0, V);
}
