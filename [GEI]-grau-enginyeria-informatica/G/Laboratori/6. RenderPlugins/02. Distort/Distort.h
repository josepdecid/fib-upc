#ifndef _GLOWING_H
#define _GLOWING_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>


class Distort : public QObject, public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")   
    Q_INTERFACES(Plugin)

    public:
        void onPluginLoad();
        bool paintGL();
 
    private:
        void drawRect(GLWidget &g);
        QOpenGLShaderProgram* program;
        QOpenGLShader* vs;
        QOpenGLShader* fs;  
        GLuint textureId;
        GLuint VAO_rect;
        QElapsedTimer elapsedTimer;
 };
 
 #endif
