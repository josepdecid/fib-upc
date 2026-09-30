#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransform ();
    void modelTransformFloor ();
    void initializeCamera ();
    void radiusContainingSphere ();
    void projectTransform ();
    void viewTransform ();
    void printIfErrors ();

    // attribute locations
    GLuint vertexLoc, colorLoc;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // Program
    QOpenGLShaderProgram *program;
    // Internal vars
    float scale;
    int rotation;
    glm::vec3 pos;

    // Model
    Model m;
    GLuint VAO_Homer;
    GLuint VBO_Homer_vertices, VBO_Homer_matdiff;

    // Camera
    float ra, fov, fovi, radius, angle, zfar, znear;
    glm::vec3 center, OBS, VRP, VUP;
};
