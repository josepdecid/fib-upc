#include "Resaltat.h"
#include "glwidget.h"

void Resaltat::onPluginLoad() {
	glwidget()->makeCurrent();
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("resaltat.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("resaltat.frag");
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	numVertices = createBuffers();
}

void Resaltat::postFrame() {
	int selected = scene()->selectedObject();
	if (selected != -1) {
		program->bind();
		GLint polygonMode;
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->viewMatrix();
		program->setUniformValue("modelViewProjectionMatrix", MVP);

		const Object &obj = scene()->objects()[selected];
		program->setUniformValue("boundingBoxMin", obj.boundingBox().min());
		program->setUniformValue("boundingBoxMax", obj.boundingBox().max());
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);
		glBindVertexArray(0);

		glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
		program->release();
	}
}

int Resaltat::createBuffers() {
	GLfloat vertices[] = {
		0, 0, 0,
		1, 0, 0,
		0, 1, 0,
		1, 1, 0, // Front
		0, 1, 1,
		1, 1, 1, // Up
		0, 0, 1,
		1, 0, 1, // Back
		0, 0, 0,
		1, 0, 0, // Bottom
		1, 0, 0,
		1, 0, 1,
		1, 1, 0,
		1, 1, 1, // Right
		1, 1, 0,
		0, 1, 1,
		0, 1, 0,
		0, 0, 1 // Left
	};
	int numVertices = sizeof(vertices) / sizeof(*vertices);
	GLfloat colors[numVertices];
	fill_n(colors, numVertices, 0);
	// VAOs
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	// VBOs
	generateVBO(verticesVBO, numVertices, &vertices[0], 0, 3);
	generateVBO(colorsVBO, numVertices, &colors[0], 2, 3);
	return numVertices;
}

void Resaltat::generateVBO(GLuint VBOId, GLsizeiptr size, GLfloat *data, GLuint attrId, GLuint attrSize) {
	glGenBuffers(1, &VBOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attrId, attrSize, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrId);
}
