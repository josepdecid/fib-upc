#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
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
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  public slots:
    void move_scene_zoom(int v);
    void set_patricio_camera(bool b);
    void set_component_R(int r);
    void set_component_G(int g);
    void set_component_B(int b);

  signals:
    void update_scene_zoom(int v);
    void update_checkbox_patricio(bool b);

  private:
    void createBuffers ();
    void carregaShaders ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    void modelTransformPatricio ();
    void modelTransformPatricio2 ();
    void updateFloor();
    void calculaCapsaModel ();
    void calculaCapsaVaca ();

    // VAO i VBO names
    GLuint VAO_Patr, VBO_PatrPos, VBO_PatrNorm, VBO_PatrMatamb, VBO_PatrMatdiff, VBO_PatrMatspec, VBO_PatrMatshin;
    GLuint VAO_Terra, VBO_TerraPos, VBO_TerraNorm, VBO_TerraMatamb, VBO_TerraMatdiff, VBO_TerraMatspec, VBO_TerraMatshin;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc, paintCowLoc, paintFrangesLoc, focusPatLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    // model
    Model patr, patr2;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centrePatr;
    float escalap1, escalap2;
    // radi de l'escena
    float radiEsc;
    float rotation;
    int paintFranges;

    typedef  enum {NONE, ROTATE, ZOOM} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY;
    bool perspectiva, FPCamera;
    float xPat;

    float fov, ra;
    float left, right, top, bottom;
    float psi, theta, phi, deltaA, deltaZ;

    float red_comp, green_comp, blue_comp;

    glm::vec3 lookPat;
};

