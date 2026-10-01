#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

out vec3 normSCO;
out vec3 vertexSCO;
out vec3 matamb1;
out vec3 matdiff1;
out vec3 matspec1;
out float matshin1;

void main()
{	
    mat3 NormalMatrix = inverse(transpose(mat3(view*TG)));
    vertexSCO = vec3(view*TG*vec4(vertex,1.0));
    normSCO = normalize(NormalMatrix*normal);
    matamb1 = matamb;
    matspec1 = matspec;
    matdiff1 = matdiff;
    matshin1 = matshin;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
