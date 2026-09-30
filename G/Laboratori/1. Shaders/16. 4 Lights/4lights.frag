#version 330 core

uniform mat4 modelViewMatrixInverse;

out vec4 fragColor;

in vec3 N;
in vec3 P;

uniform float time;
uniform bool rotate = true;

const float shininess = 100.0;
const float Kd = 0.5;

vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor) {
	vec3 lpos = (modelViewMatrixInverse * vec4(lightPos, 1)).xyz;
	vec3 L = normalize(lpos - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N, L));
	float RdotV = max(0.0, dot(R, V));
	float spec = pow(RdotV, shininess);
	return vec4(Kd*lightColor*NdotL + vec3(spec), 0);
}

void main() {
	vec3 V = normalize((modelViewMatrixInverse * vec4(0, 0, 0, 1)).xyz - P);
	vec3 NE = normalize(N);

	vec3 g_pos = vec3(0, 10, 0),  g_col = vec3(0, 1, 0);
	vec3 y_pos = vec3(0, -10, 0), y_col = vec3(1, 1, 0);
	vec3 b_pos = vec3(10, 0, 0),  b_col = vec3(0, 0, 1);
	vec3 r_pos = vec3(-10, 0, 0), r_col = vec3(1, 0, 0);

	if (rotate) {
		float c = cos(time), s = sin(time);
		mat3 rot = mat3(
			vec3(c, s, 0),
			vec3(-s, c, 0),
			vec3(0, 0, 1)
		);

		g_pos = rot * g_pos;
		y_pos = rot * y_pos;
		b_pos = rot * b_pos;
		r_pos = rot * r_pos;
	}

	vec4 color = vec4(0);
	color += light(V, NE, P, g_pos, g_col);
	color += light(V, NE, P, y_pos, y_col);
	color += light(V, NE, P, b_pos, b_col);
	color += light(V, NE, P, r_pos, r_col);
	fragColor = color;
}

