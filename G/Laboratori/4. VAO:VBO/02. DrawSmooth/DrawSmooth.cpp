#include "DrawSmooth.h"
#include "glwidget.h"
#include <cassert>
#include <cmath>

DrawSmooth::~DrawSmooth() {
    cleanUp();
}

void DrawSmooth::onSceneClear() {
    cleanUp();
}

void DrawSmooth::cleanUp() {
    glDeleteBuffers(vertexBuffers.size(), &vertexBuffers.front());
    glDeleteBuffers(colorBuffers.size(), &colorBuffers.front());
    glDeleteBuffers(normalBuffers.size(), &normalBuffers.front());
    glDeleteBuffers(texCoordsBuffers.size(), &texCoordsBuffers.front());
    glDeleteBuffers(indexBuffers.size(), &indexBuffers.front());
    glDeleteVertexArrays(VAOs.size(), &VAOs.front());

    vertexBuffers.clear();
    colorBuffers.clear();
    normalBuffers.clear();
    texCoordsBuffers.clear();
    indexBuffers.clear();
    VAOs.clear();
}

bool DrawSmooth::drawScene() {
    for (unsigned int i = 0; i < VAOs.size(); ++i) {
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);
    } glBindVertexArray(0);
    return true;
}

bool DrawSmooth::drawObject(int i) {
    glBindVertexArray(VAOs[i]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[i]);
	glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*) 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return true;
}

void DrawSmooth::onPluginLoad() {
  for (unsigned int i = 0; i < scene()->objects().size(); ++i) addVBO(i);
}

void DrawSmooth::onObjectAdd() {
  addVBO(scene()->objects().size() - 1);
}

void DrawSmooth::addVBO(unsigned int currentObject) {
    // Create and fill the four arrays (vertex coords, vertex normals, and face indices)
    // Each coordinate/normal appears only once (1 normal for each vertex)
    vector<float> vertices;  // (x,y,z)    Final size: 3*number of vertices
    vector<float> normals;   // (nx,ny,nz) Final size: 3*number of vertices
    vector<float> colors;    // (r, g, b)  Final size: 3*number of vertices
    vector<float> texCoords; // (s, t)     Final size: 3*number of vertices
    vector<int> indices;

    // Each vertex appears once in our VBO, with a unique normal value.
    // Hence, all faces that use that vertex use the same normal, color and texture coords.
    const Object &obj = scene()->objects()[currentObject];
    const vector<Vertex> &verts = obj.vertices();
    const vector<Face> &faces = obj.faces();

    vector<Vector> VN(verts.size(), Vector(0, 0, 0));
    vector<int> VC(verts.size(), 0);
    for (const Face &face: faces) {
        const Vector &N = face.normal().normalized();
        for (unsigned int i = 0; i < (unsigned int)face.numVertices(); ++i) {
            VN[face.vertexIndex(i)] += N;
            ++VC[face.vertexIndex(i)];
        }
    }

    for (unsigned int i = 0; i < verts.size(); ++i) {
        const Vector N = VN[i] / VC[i];
        const Point &P = verts[i].coord();
        float r = obj.boundingBox().radius();
        float s = Vector::dotProduct((1.0/r) * Vector(1, 0, 1), P);
        float t = Vector::dotProduct((1.0/r) * Vector(0, 1, 0), P);
        if ((int)verts.size() == 81) { // Special case for plane
            s = 0.5f*(P.x() + 1);
            t = 0.5f*(P.y() + 1);
        } else if ((int)verts.size() == 386) { // Special case for cube
            s = Vector::dotProduct((1.0/2.0)*Vector(1, 0, 1), P);
            t = Vector::dotProduct((1.0/2.0)*Vector(0, 1, 0), P);
        }

        // Add vertices
        vertices.push_back(P.x());
        vertices.push_back(P.y());
        vertices.push_back(P.z());
        // Add colors
        colors.push_back(abs(N.x()));
        colors.push_back(abs(N.y()));
        colors.push_back(abs(N.z()));
        // Add normals
        normals.push_back(N.x());
        normals.push_back(N.y());
        normals.push_back(N.z());
        // Add textures
        texCoords.push_back(s);
        texCoords.push_back(t);
    }

    // Set indices
    for (const Face &face : faces) {
        for (unsigned int i = 0; i < (unsigned int)face.numVertices(); ++i) { 
            indices.push_back(face.vertexIndex(i));
        }
    }

    // Create empty buffers and set VBO data
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    generateVBO(vertices, vertexBuffers, 0, 3, currentObject);
    generateVBO(colors, colorBuffers, 1, 3, currentObject);
    generateVBO(normals, normalBuffers, 2, 3, currentObject);
    generateVBO(texCoords, texCoordsBuffers, 3, 2, currentObject);

    GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
    indexBuffers.push_back(indexBufferID);
    numIndices.push_back(indices.size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[currentObject]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void DrawSmooth::generateVBO(vector<float> &data, vector<GLuint> &buffers, int attrPos, int attrSize, unsigned int idx) {
    GLuint bufferID;
	glGenBuffers(1, &bufferID);
    buffers.push_back(bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[idx]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), &data.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(attrPos, attrSize, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attrPos);
}