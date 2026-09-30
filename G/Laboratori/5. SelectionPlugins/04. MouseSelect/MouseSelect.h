#ifndef _MOUSESELECT_H
#define _MOUSESELECT_H

#include "plugin.h" 

class MouseSelect: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();

		void mouseReleaseEvent(QMouseEvent *);
	private:
		void encodeID(int index, GLubyte *color);
		int decodeID(GLubyte *color);
		QOpenGLShaderProgram* program;
		QOpenGLShader* vs;	
    	QOpenGLShader* fs;
};

#endif
