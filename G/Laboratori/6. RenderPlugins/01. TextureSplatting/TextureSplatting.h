#ifndef _MULTITEX_H
#define _MULTITEX_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class TextureSplatting : public QObject, public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

    public:
        void onPluginLoad();
        void preFrame();
        void postFrame();
    
    private:
        void loadTexture(GLuint tex, GLuint textureId);
        QOpenGLShaderProgram* program;
        QOpenGLShader* vs;
        QOpenGLShader* fs; 
        GLuint textureId0, textureId1, textureId2;
 };
 
 #endif
