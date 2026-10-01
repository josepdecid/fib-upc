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
    // mouse
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransformP1 ();
    void modelTransformP2 ();
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
    Model m1;
    GLuint VAO_Patricio1;
    GLuint VBO_Patricio1_vertices, VBO_Patricio1_matdiff;

    Model m2;
    GLuint VAO_Patricio2;
    GLuint VBO_Patricio2_vertices, VBO_Patricio2_matdiff;

    GLuint VAO_Floor;
    GLuint VBO_Floor_vertices, VBO_Floor_colors;

    // Camera
    float ra, fov, fovi, radius, deltaFOV, zfar, znear;
    glm::vec3 center, centerBase, OBS, VRP, VUP;
    float top, bottom, left, right, topIni, bottomIni, leftIni, rightIni;

    // Mouse
    typedef enum {NOINTERACTION, ROTATION} Interaction;
    Interaction interaction, interactionZoom;
    glm::vec3 xAxis, yAxis, zAxis;
    float psi, phi, theta, deltaA;
    int xClick, yClick;
};
