#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat4 projectionMatrix;

const float areamax = 0.0005;
const vec4 Red = vec4(1, 0, 0, 1);
const vec4 Yellow = vec4(1, 1, 0, 1);

void main() {
	vec3 areaVec = cross(
		(gl_in[1].gl_Position - gl_in[0].gl_Position).xyz,
		(gl_in[2].gl_Position - gl_in[0].gl_Position).xyz
	);
	float area = length(areaVec) / 2 / areamax;
	for (int i = 0; i < 3; ++i) {
		gfrontColor = mix(Red, Yellow, area);
		gl_Position = projectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
