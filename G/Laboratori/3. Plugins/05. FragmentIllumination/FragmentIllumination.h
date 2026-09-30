#ifndef _FRAGMENTILLUMINATION_H
#define _FRAGMENTILLUMINATION_H

#include "plugin.h" 

class FragmentIllumination: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	void onPluginLoad();
	void preFrame();
	void postFrame();
  private:
	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;	
    QOpenGLShader* fs;
};

#endif
