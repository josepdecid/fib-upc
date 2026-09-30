#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vNormal[];
in vec4 vfrontColor[];

out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

const float speed = 0.5;

void main() {
	vec3 n = (vNormal[0] + vNormal[1] + vNormal[2]) / 3;
	vec3 translation = speed * time * n;
	for (int i = 0; i < 3; i++) {
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * vec4(gl_in[i].gl_Position.xyz + translation, 1);
		EmitVertex();
	}
    EndPrimitive();
}