#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "QKeyEvent"
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_FORCE_RADIANS

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();

    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);

    // Per rebre events de teclat
    virtual void keyPressEvent (QKeyEvent *e);

  private:
    void createBuffers ();
    void carregaShaders ();
    void transformModel ();

    // attribute locations
    GLuint vertexLoc;

    // Program
    QOpenGLShaderProgram *program;

    // Matriu de Transformacions Geometriques
    GLuint translationLoc;
    float tx, ty, tz;

    // Scale
    GLuint varLoc;
    float scl;

    GLuint VAO, VBO, VBO_Color;
    GLuint colorLoc;
};
