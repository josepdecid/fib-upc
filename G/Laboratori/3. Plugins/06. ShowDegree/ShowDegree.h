  #ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include <sstream>
#include <QPainter>
#include "plugin.h"

class ShowDegree: public QObject, public Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin") 
  Q_INTERFACES(Plugin)

  public:
    void onPluginLoad();
    void postFrame();

    void onObjectAdd();
    void onSceneClear();
  private:
    GLuint textureID;
    QOpenGLShaderProgram *program;
    QOpenGLShader *vs;
    QOpenGLShader *fs;
    
    float degree;

    void drawRect(GLWidget &g);
    void updateCounter();
};

#endif
