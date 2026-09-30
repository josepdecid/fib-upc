#ifndef _DRAW_VBONG_H
#define _DRAW_VBONG_H

#include <vector>
#include "plugin.h"

using namespace std;

class DrawSmooth : public QObject, public Plugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")   
    Q_INTERFACES(Plugin)

    public:
        ~DrawSmooth();
        void cleanUp();
 
        void onSceneClear();
        void onPluginLoad();
        void onObjectAdd();
        bool drawScene();
        bool drawObject(int i);
    private:
        void addVBO(unsigned int currentObject);
        void generateVBO(vector<float> &data, vector<GLuint> &buffers, int attrPos, int attrSize, unsigned int idx);
        vector<GLuint> VAOs;             // ID of VAOs
        vector<GLuint> vertexBuffers;    // ID of vertex coordinates buffer 
        vector<GLuint> normalBuffers;    // ID of normal components buffer 
        vector<GLuint> texCoordsBuffers; // ID of (s,t) buffer 
        vector<GLuint> colorBuffers;     // ID of color buffer  
        vector<GLuint> indexBuffers;     // ID of index buffer
        vector<GLuint> numIndices;       // Size (number of indices) in each index buffer
};
 
#endif
