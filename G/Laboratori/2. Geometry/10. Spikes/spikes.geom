#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vNormal[];
out vec4 gfrontColor;
out vec4 gnormal;

uniform mat4 modelViewProjectionMatrix;
uniform float disp = 0.05;

void main() {
	vec3 baricenter = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3).xyz;
	vec3 normal = normalize(vNormal[0] + vNormal[1] + vNormal[2]);
	vec4 pick = vec4(baricenter + normal * disp, 1);

	gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
	gfrontColor = vfrontColor[0]; EmitVertex();
	gl_Position = modelViewProjectionMatrix * gl_in[1].gl_Position;
	gfrontColor = vfrontColor[1]; EmitVertex();
	gl_Position = modelViewProjectionMatrix * pick;
	gfrontColor = vec4(1); EmitVertex();
	gl_Position = modelViewProjectionMatrix * gl_in[2].gl_Position;
	gfrontColor = vfrontColor[2]; EmitVertex();
	gl_Position = modelViewProjectionMatrix * gl_in[0].gl_Position;
	gfrontColor = vfrontColor[0]; EmitVertex();
    EndPrimitive();
}
