#include "ShowDegree.h"
#include "glwidget.h"

const int SIZE = 1024;

void ShowDegree::onPluginLoad() {
	glwidget()->makeCurrent();
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("show-degree.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("show-degree.frag");
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	updateCounter();
}	

void ShowDegree::postFrame() {
	GLWidget &g = *glwidget();
	g.makeCurrent();

	// Create image with text
	QImage image(SIZE, SIZE, QImage::Format_RGB32);
	image.fill(Qt::white);
	QPainter painter;
	painter.begin(&image);
	QFont font;
	font.setPixelSize(32);
	painter.setFont(font);
	painter.setPen(QColor(0, 0, 0));

	if (degree != -1) {
		stringstream textDisp;
		textDisp << "Degree: " << degree;
		painter.drawText(15, 50, QString(textDisp.str().c_str()));
		textDisp.str(string());
	}
	
	painter.end();

	// Create texture
	const int textureUnit = 5;
	g.glActiveTexture(GL_TEXTURE0 + textureUnit);
	QImage im0 = image.mirrored(false, true).convertToFormat(QImage::Format_RGBA8888, Qt::ColorOnly);
	g.glGenTextures(1, &textureID);
	g.glBindTexture(GL_TEXTURE_2D, textureID);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Draw quad using texture
	program->bind();
	program->setUniformValue("colorMap", textureUnit);
	program->setUniformValue("WIDTH", float(glwidget()->width()));
	program->setUniformValue("HEIGHT", float(glwidget()->height()));

	// Quad covering viewport
	drawRect(g);
	program->release();
	g.glBindTexture(GL_TEXTURE_2D, 0);

	g.glDeleteTextures(1, &textureID);
}

void ShowDegree::onObjectAdd() {
	updateCounter();
}

void ShowDegree::onSceneClear() {
	updateCounter();	
}

void ShowDegree::drawRect(GLWidget &g) {
	static bool created = false;
	static GLuint VAO_rect;

	// Create VBO Buffers
	if (!created) {
		created = true;
		
		// Create & bind empty VAO
		g.glGenVertexArrays(1, &VAO_rect);
		g.glBindVertexArray(VAO_rect);
		float z = -0.99999;
		
		// Create VBO with (x,y,z) coordinates
		float coords[] = { -1, -1, z, 1, -1, z, -1, 1, z, 1, 1, z };
		
		GLuint VBO_coords;
		g.glGenBuffers(1, &VBO_coords);
		g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
		g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
		g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		g.glEnableVertexAttribArray(0);
		g.glBindVertexArray(0);
	}

	// Draw
	g.glBindVertexArray(VAO_rect);
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	g.glBindVertexArray(0);
}

void ShowDegree::updateCounter() {
	int vertices = 0;
	for (Object o : scene()->objects())
		vertices += o.vertices().size();

	vector<int> degrees(vertices, 0);
	for (Object o : scene()->objects())
		for (Face f : o.faces())
			for (int i = 0; i < f.numVertices(); ++i)
				++degrees[f.vertexIndex(i)];
	
	degree = 0;
	for (unsigned int i = 0; i < degrees.size(); ++i)
		degree += degrees[i];
	degree = degrees.size() == 0 ? -1 : degree / degrees.size();
}