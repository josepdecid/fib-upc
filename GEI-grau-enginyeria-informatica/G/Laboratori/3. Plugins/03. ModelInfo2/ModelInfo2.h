#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include <sstream>
#include <QPainter>
#include "plugin.h"

class ModelInfo2: public QObject, public Plugin {
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
    
    int objectCount;
    int polygonCount;
    int vertexCount;
    float trianglePercent;

    void updateCounters();
    void drawRect(GLWidget &g);
};

#endif
