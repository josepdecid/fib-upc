#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vNormal[];
in vec4 vfrontColor[];

out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

const float speed = 0.1;
const float angSpeed = 8.0;

void main() {
	vec3 n = (vNormal[0] + vNormal[1] + vNormal[2]) / 3;
	vec3 translation = speed * time * n;
	vec3 baricenter = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3).xyz;
	float phi = angSpeed * time, s = sin(phi), c = cos(phi);
	mat3 rot = mat3(
		vec3(c, s, 0),
		vec3(-s, c, 0),
		vec3(0, 0, 1)
	);
	for (int i = 0; i < 3; i++) {
		gfrontColor = vfrontColor[i];
		vec4 v = vec4(rot * (gl_in[i].gl_Position.xyz - baricenter) + baricenter + translation, 1);
		gl_Position = modelViewProjectionMatrix * v;
		EmitVertex();
	}
    EndPrimitive();
}