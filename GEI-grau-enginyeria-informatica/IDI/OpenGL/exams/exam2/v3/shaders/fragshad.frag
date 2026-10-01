#version 330 core

in vec3 fcolor;
out vec4 FragColor;

uniform int paintFranges;

void main()
{
	if (paintFranges == 1) {
		if ((int (gl_FragCoord.y) / 10) % 2 == 0) {
			FragColor = vec4(0, 0, 0, 1);
		}
		else {
			FragColor = vec4(1, 1, 1, 1);
		}
	}
	else {
		FragColor = vec4(fcolor,1);
	}
}
