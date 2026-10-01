#include "AnimateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad() {
	glwidget()->makeCurrent();
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("animate-vertices.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("animate-vertices.frag");
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	elapsedTimer.start();
}

void AnimateVertices::preFrame() {
	program->bind();

	QMatrix4x4 MVP_M = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 N_M = camera()->viewMatrix().normalMatrix();
	float T = elapsedTimer.elapsed() / 1000.0;
	
	program->setUniformValue("modelViewProjectionMatrix", MVP_M);
	program->setUniformValue("normalMatrix", N_M);
	program->setUniformValue("time", T);
}

void AnimateVertices::postFrame() {
	program->release();
}