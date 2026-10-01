#include "MouseSelect.h"
#include "glwidget.h"

void MouseSelect::onPluginLoad() {
	glwidget()->makeCurrent();

	QString vsSrc =
		"#version 330 core\n"
		"layout (location=0) in vec3 vertex;\n"
		"uniform mat4 modelViewProjectionMatrix;\n"
		"void main() {\n"
    	"	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1);\n"
		"}";
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceCode(vsSrc);

	QString fsSrc =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"uniform vec4 color;\n"
		"void main() {\n"
    	"	fragColor = color;\n"
		"}";
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceCode(fsSrc);

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
}

void MouseSelect::mouseReleaseEvent(QMouseEvent *event) {
	// Only control + Left click
	if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier) {
		// Clear background color buffers
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Bind program
		program->bind();
		// Send uniforms
		QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->viewMatrix();
		program->setUniformValue("modelViewProjectionMatrix", MVP);
		// Print colored objects
		for (int i = 0; i < (int)scene()->objects().size(); ++i) {
			GLubyte color[4];
			encodeID(i, color);
			QVector4D c = QVector4D(color[0]/255.0, color[1]/255.0, color[2]/255.0, 1.0);
			program->setUniformValue("color", c);
			drawPlugin()->drawObject(i);
		} program->release();
		// Read color buffer under mouse
		int x = event->x();
		int y = glwidget()->height() - event->y();
		GLubyte read[4];
		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
		// Set selected object
		int id = decodeID(read);
		if (id < 0 || id >= (int)scene()->objects().size()) id = -1;
		scene()->setSelectedObject(id);
		// Update
		glwidget()->update();
		cout << scene()->selectedObject() << endl;
	}
}

void MouseSelect::encodeID(int index, GLubyte *color) {
	color[0] = color[1] = color[2] = index;
}

int MouseSelect::decodeID(GLubyte *color) {
	if (color[0] == 255) return -1;
	return color[0];
}
