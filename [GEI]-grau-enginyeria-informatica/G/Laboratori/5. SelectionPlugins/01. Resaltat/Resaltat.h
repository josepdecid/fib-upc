#ifndef _RESALTAT_H
#define _RESALTAT_H

#include "plugin.h" 

class Resaltat: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  	public:
	  	void onPluginLoad();
		void postFrame();
	private:
		void generateVBO(GLuint VBOId, GLsizeiptr size, GLfloat *data, GLuint attrId, GLuint attrSize);
		int createBuffers();
		int numVertices;
		GLuint cubeVAO;
		GLuint verticesVBO;
		GLuint colorsVBO;
		QOpenGLShaderProgram* program;
		QOpenGLShader* vs;	
    	QOpenGLShader* fs;
};

#endif
