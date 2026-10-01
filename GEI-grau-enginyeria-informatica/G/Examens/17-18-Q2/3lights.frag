#version 330 core

in vec3 N;
in vec3 P;

out vec4 fragColor;

uniform vec4 matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightSpecular;

uniform mat4 modelViewMatrix;

vec4 lightContribution(vec4 lightDiff, vec4 lightPos, vec3 normal, vec3 V) {
    vec3 L = lightPos.xyz;
	vec3 R = reflect(-L, normal);
    float dotNL = max(0.0, dot(normal, L));
    float dotRV = pow(max(0.0, dot(R, V)), matShininess);
    return matDiffuse * lightDiff * dotNL + matSpecular * lightSpecular * dotRV;
}

void main() {
    vec4 r_pos = modelViewMatrix * vec4(1, 0, 0, 0);
    vec4 r_col = vec4(1, 0, 0, 1);
    vec4 g_pos = modelViewMatrix * vec4(0, 1, 0, 0);
    vec4 g_col = vec4(0, 1, 0, 1);
    vec4 b_pos = modelViewMatrix * vec4(0, 0, 1, 0);
    vec4 b_col = vec4(0, 0, 1, 1);

    vec3 NN = normalize(N);
    vec3 NV = normalize(-P);
         
    vec4 color = vec4(0);
    color += lightContribution(r_col, r_pos, NN, NV);
    color += lightContribution(g_col, g_pos, NN, NV);
    color += lightContribution(b_col, b_pos, NN, NV);
    fragColor = color;
}
