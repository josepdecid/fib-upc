#version 330 core

out vec4 FragColor;
in vec4 colorO;

void main() {
	FragColor = colorO;
}