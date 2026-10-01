#version 330 core

in vec4 V;
in vec3 NE;

out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform sampler2D noise;

const vec4 white = vec4(1);
const vec4 redish = vec4(.5, .2, .5, 1);

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
    vec3 lightPos = vec3(0, 0, 2);
    vec3 L = normalize(lightPos - Pos);
    vec3 V = normalize(-Pos);
    vec3 R = reflect(-L, N);
    float NdotL = max(0.0, dot(N, L));
    float RdotV = max(0.0, dot(R, V));
    float Ispec = pow(RdotV, 20);
    return diffuse * NdotL + Ispec;
}

void main() {
    vec4 sp = 0.3 * vec4(0, 1, -1, 0);
    vec4 tp = 0.3 * vec4(-2, -1, 1, 0);
    float s = dot(sp, V);
    float t = dot(tp, V);

    float v = texture(noise, vec2(s, t)).x;
    vec4 diff = v < 0.5
        ? mix(white, redish, v*2)
        : mix(redish, white, (v - 0.5)*2);
    
    vec3 Pos = (modelViewMatrix * V).xyz;
    fragColor = shading(normalize(NE), Pos, diff);
}
