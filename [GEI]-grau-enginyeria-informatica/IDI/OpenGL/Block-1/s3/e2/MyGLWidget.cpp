#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();

  scale = 1.0;
  glUniform1f(scaleLoc, scale);

  tx = ty = tz = 0.0;
  transformModel();
}

void MyGLWidget::paintGL ()
{
  // Esborrem el frame-buffer i depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem l'Array a pintar
  glBindVertexArray(VAO);

  transformModel();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 4);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  glViewport (0, 0, w, h);
}

void MyGLWidget::createBuffers ()
{
  glm::vec3 Color[4];  // Tres vèrtexs amb X, Y i Z
  Color[0] = glm::vec3(1.0, 0.0, 0.0);
  Color[1] = glm::vec3(0.0, 1.0, 0.0);
  Color[2] = glm::vec3(0.0, 0.0, 1.0);
  Color[3] = glm::vec3(1.0, 1.0, 0.0);

  glm::vec3 Vertices[6];  // Sis vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-0.5, -0.5, 0.0);
  Vertices[1] = glm::vec3(0.5, -0.5, 0.0);
  Vertices[2] = glm::vec3(-0.5, 0.5, 0.0);
  Vertices[3] = glm::vec3(-0.5, 0.5, 0.0);
  Vertices[4] = glm::vec3(0.5, -0.5, 0.0);
  Vertices[5] = glm::vec3(0.5, 0.5, 0.0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Afegim els colors al VBO correspontent
  glGenBuffers(1, &VBO_Color);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per colors
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  scaleLoc = glGetAttribLocation (program->programId(), "scale");
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  translationLoc = glGetUniformLocation(program->programId(), "matrix");
}

void MyGLWidget::keyPressEvent (QKeyEvent *e)
{
  makeCurrent();
  switch (e->key()) {
    case Qt::Key_Escape:
      exit(0);
    case Qt::Key_Q:
      scale += 0.1;
      glUniform1f(scaleLoc, scale);
      break;
    case Qt::Key_W:
      scale -= 0.1;
      glUniform1f(scaleLoc, scale);
      break;
    case Qt::Key_Left:
      tx -= 0.1;
      break;
    case Qt::Key_Right:
      tx += 0.1;
      break;
    case Qt::Key_Up:
      ty += 0.1;
      break;
    case Qt::Key_Down:
      ty -= 0.1;
      break;
    default:
     e->ignore();
  }
  update();
}

void MyGLWidget::transformModel ()
{
  glm::mat4 TG(1.0); // Matriu de transformació, inicialment la identitat
  TG = glm::translate (TG, glm::vec3 (tx, ty, tz));
  TG = glm::rotate (TG, float(M_PI / 4.0), glm::vec3(0, 1, 1.0));
  glUniformMatrix4fv (translationLoc, 1, GL_FALSE, &TG[0][0]);
}
