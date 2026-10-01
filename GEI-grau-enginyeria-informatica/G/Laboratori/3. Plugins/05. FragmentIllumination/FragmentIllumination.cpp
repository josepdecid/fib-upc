#include "FragmentIllumination.h"
#include "glwidget.h"

void FragmentIllumination::onPluginLoad() {
	glwidget()->makeCurrent();
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("lighting.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("lighting.frag");
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
}

void FragmentIllumination::preFrame() {
	program->bind();

	QMatrix4x4 MV_M = camera()->viewMatrix();
	QMatrix4x4 MVP_M = camera()->projectionMatrix() * camera()->viewMatrix();
	QMatrix3x3 N_M = camera()->viewMatrix().normalMatrix();
	
	program->setUniformValue("modelViewMatrix", MV_M);
	program->setUniformValue("modelViewProjectionMatrix", MVP_M);
	program->setUniformValue("normalMatrix", N_M);

    program->setUniformValue("lightAmbient", QVector4D(Vector(0.1, 0.1, 0.1), 1));
    program->setUniformValue("lightDiffuse", QVector4D(Vector(1, 1, 1), 1));
    program->setUniformValue("lightSpecular", QVector4D(Vector(1, 1, 1), 1));
    program->setUniformValue("lightPosition", QVector4D(0, 0, 0, 1));

    program->setUniformValue("matAmbient", QVector4D(Vector(0.8, 0.8, 0.6), 1));
    program->setUniformValue("matDiffuse", QVector4D(Vector(0.8, 0.8, 0.6), 1));
    program->setUniformValue("matSpecular", QVector4D(Vector(1.0, 1.0, 1.0), 1));
	program->setUniformValue("matShininess", GLfloat(64.0));
}

void FragmentIllumination::postFrame() {
	program->release();
}