#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
  rotation = 0;
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

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  m.load("../../models/Patricio.obj");

  carregaShaders();
  createBuffers();

  initializeCamera();

  printIfErrors();

  glEnable(GL_DEPTH_TEST);
}

void MyGLWidget::paintGL ()
{
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform ();

  // Activem el VAO per a pintar la caseta
  glBindVertexArray (VAO_Homer);
  // pintem
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransform ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::translate(transform, -center);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformFloor ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform()
{
  // glm::perspective(FOV (radians), ra window, znear, zfar);
  glm::mat4 Proj = glm::perspective(fov, ra, znear, zfar);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
  //glm::lookAt(OBS, VRP, UP)
  glm::mat4 View = glm::lookAt(OBS, VRP, VUP);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::initializeCamera()
{
  radiusContainingSphere();

  OBS = glm::vec3(0.0, 0.0, 1.5 * radius);
  VRP = glm::vec3(0.0, 0.0, 0.0);
  VUP = glm::vec3(0.0, 1.0, 0.0);

  float d = sqrt(
    (OBS[0] - VRP[0]) * (OBS[0] - VRP[0]) +
    (OBS[1] - VRP[1]) * (OBS[1] - VRP[1]) +
    (OBS[2] - VRP[2]) * (OBS[2] - VRP[2])
  );

  znear = (d - radius) / 2.0;
  zfar = d + radius;

  ra = 1.0;
  fov = fovi = (float) M_PI / 2.0;
  angle = 0.0;

  viewTransform();
  projectTransform();
}

void MyGLWidget::radiusContainingSphere()
{
  float xmin = m.vertices()[0];
  float ymin = m.vertices()[1];
  float zmin = m.vertices()[2];
  float xmax = m.vertices()[0];
  float ymax = m.vertices()[1];
  float zmax = m.vertices()[2];

  for (unsigned int i = 3; i < m.vertices().size(); i += 3) {
    if (m.vertices()[i+0] < xmin)
      xmin = m.vertices()[i+0];
    if (m.vertices()[i+0] > xmax)
      xmax = m.vertices()[i+0];
    if (m.vertices()[i+1] < ymin)
      ymin = m.vertices()[i+1];
    if (m.vertices()[i+1] > ymax)
      ymax = m.vertices()[i+1];
    if (m.vertices()[i+2] < zmin)
      zmin = m.vertices()[i+2];
    if (m.vertices()[i+2] > zmax)
      zmax = m.vertices()[i+2];
  }

  float dx = xmax - xmin;
  float dy = ymax - ymin;
  float dz = zmax - zmin;

  radius = sqrt(dx*dx + dy*dy + dz*dz) / 2.0;
  center[0] = (xmax + xmin) / 2.0;
  center[1] = (ymax + ymin) / 2.0;
  center[2] = (zmax + zmin) / 2.0;
}

void MyGLWidget::resizeGL (int w, int h)
{
  ra = float(w) / float(h);
  if (ra < 1.0) {
    fov = 2.0 * atan(tan(fovi/2.0) / ra);
  }
  glViewport(0, 0, w, h);
  projectTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    case Qt::Key_R: {
      rotation = (rotation + 1) % 8;
      modelTransform();
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::createBuffers ()
{
  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  glGenBuffers(1, &VBO_Homer_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer_vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_Homer_matdiff);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer_matdiff);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
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
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::printIfErrors() {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
  }
}
