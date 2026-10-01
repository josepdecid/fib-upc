#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
  rotation = 0;

  xClick = yClick = 0;
  deltaA = M_PI / 180.0;
  deltaFOV = M_PI / 50.0;
  interaction = interactionZoom = NOINTERACTION;
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
  m1.load("../../models/Patricio.obj");
  m2.load("../../models/Patricio.obj");

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
  modelTransformP1 ();

  // Activem el VAO per a pintar la caseta
  glBindVertexArray (VAO_Patricio1);
  // pinteminitializeCamera
  glDrawArrays(GL_TRIANGLES, 0, m1.faces().size() * 3);

  modelTransformP2 ();

  glBindVertexArray (VAO_Patricio2);
  glDrawArrays(GL_TRIANGLES, 0, m2.faces().size() * 3);

  // Carreguem la transformació del model
  modelTransformFloor ();
  
  glBindVertexArray (VAO_Floor);
  // pintem
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransformP1 ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::translate(transform, glm::vec3(1.0, 0, 1.0));
  transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
  transform = glm::translate(transform, -centerBase);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformP2 ()
{
  // Matriu de transformació del model
  glm::mat4 transform (1.0f);
  transform = glm::translate(transform, glm::vec3(-1.0, 0, -1.0));
  transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
  transform = glm::rotate(transform, float(M_PI), glm::vec3(0, 1, 0));
  transform = glm::translate(transform, -centerBase);
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
  //glm::mat4 Proj = glm::perspective(fov, ra, znear, zfar);
  // glm::mat4 Proj = glm::ortho (left, right, bottom, top, ZNear, ZFar)
  glm::mat4 Proj = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, znear, zfar);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
  //glm::lookAt(OBS, VRP, UP)
  glm::mat4 view(1.0f);
  view = glm::translate(view, -OBS); // Camera to origin
  view = glm::rotate(view, -psi, yAxis); // Rotate
  view = glm::rotate(view, theta, xAxis);
  view = glm::rotate(view, phi, zAxis);
  view = glm::translate(view, -VRP); // VRP to origin
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
  printIfErrors();
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

  xAxis = glm::vec3(1.0, 0.0, 0.0);
  yAxis = glm::vec3(0.0, 1.0, 0.0);
  zAxis = glm::vec3(0.0, 0.0, 1.0);
  phi = psi = 0.0;
  theta = 0.5;

  viewTransform();
  projectTransform();
}

void MyGLWidget::radiusContainingSphere()
{
  float xmin = m1.vertices()[0];
  float ymin = m1.vertices()[1];
  float zmin = m1.vertices()[2];
  float xmax = m1.vertices()[0];
  float ymax = m1.vertices()[1];
  float zmax = m1.vertices()[2];

  for (unsigned int i = 3; i < m1.vertices().size(); i += 3) {
    if (m1.vertices()[i+0] < xmin)
      xmin = m1.vertices()[i+0];
    if (m1.vertices()[i+0] > xmax)
      xmax = m1.vertices()[i+0];
    if (m1.vertices()[i+1] < ymin)
      ymin = m1.vertices()[i+1];
    if (m1.vertices()[i+1] > ymax)
      ymax = m1.vertices()[i+1];
    if (m1.vertices()[i+2] < zmin)
      zmin = m1.vertices()[i+2];
    if (m1.vertices()[i+2] > zmax)
      zmax = m1.vertices()[i+2];
  }

  float dx = xmax - xmin;
  float dy = ymax - ymin;
  float dz = zmax - zmin;

  radius = sqrt(dx*dx + dy*dy + dz*dz) / 2.0;
  center[0] = (xmax + xmin) / 2.0;
  center[1] = (ymax + ymin) / 2.0;
  center[2] = (zmax + zmin) / 2.0;

  centerBase[0] = (xmax + xmin) / 2.0;
  centerBase[1] = ymin;
  centerBase[2] = (zmax + zmin) / 2.0;
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
    case Qt::Key_Z: { // zoom-in
      fovi -= deltaFOV;
      fov = fovi = (fovi < 0.5) ? 0.5 : fovi;
      projectTransform();
      break;
      case Qt::Key_X: { // zoom-out
    }
      fovi += deltaFOV;
      fov = fovi = (fovi > 3.0) ? 3.0 : fovi;
      projectTransform();
      break;
    }
    default: event->ignore(); break;
  }

  update();
}

void MyGLWidget::mousePressEvent(QMouseEvent* event)
{
  makeCurrent();
  xClick = event->x();
  yClick = event->y();
  interaction = (event->button() & Qt::LeftButton)
    ? ROTATION
    : NOINTERACTION;
  interactionZoom = (event->button() & Qt::RightButton)
    ? ROTATION
    : NOINTERACTION;
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
  makeCurrent();
  interaction = interactionZoom = NOINTERACTION;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* event)
{
  makeCurrent();
  int dx = abs(event->x() - xClick);
  int dy = abs(event->y() - yClick);

  if (interaction == ROTATION) { // Movement
    if (dx > dy) {
      if (event->x() > xClick) {
        psi -= abs(event->x() - xClick) * deltaA;
      } else if (event->x() < xClick) {
        psi += abs(event->x() - xClick) * deltaA;
      }
    } else {
      if (event->y() > yClick) {
        theta += abs(event->y() - yClick) * deltaA;
      } else if (event->y() < yClick) {
        theta -= abs(event->y() - yClick) * deltaA;
      }
    }
    viewTransform();
  } else if (interactionZoom == ROTATION) { // Zoom
    fovi += (event->y() - yClick) * deltaA;
    fov = fovi = (fovi > 3.0) ? 3.0 : (fovi < 0.5) ? 0.5 : fovi;
    projectTransform();
  }
  update();

  xClick = event->x();
  yClick = event->y();
}

void MyGLWidget::createBuffers ()
{
  // Patricio 1

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Patricio1);
  glBindVertexArray(VAO_Patricio1);

  glGenBuffers(1, &VBO_Patricio1_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio1_vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m1.faces().size() * 3 * 3, m1.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_Patricio1_matdiff);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio1_matdiff);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m1.faces().size() * 3 * 3, m1.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Patricio 2

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Patricio2);
  glBindVertexArray(VAO_Patricio2);

  glGenBuffers(1, &VBO_Patricio2_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio2_vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m2.faces().size() * 3 * 3, m2.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_Patricio2_matdiff);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio2_matdiff);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m2.faces().size() * 3 * 3, m2.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // TERRA

  glm::vec3 VFvectices[6];  // Tres vèrtexs amb X, Y i Z
  VFvectices[0] = glm::vec3(-2.0, 0.0, -2.0);
  VFvectices[1] = glm::vec3(2.0, 0.0, -2.0);
  VFvectices[2] = glm::vec3(-2.0, 0.0, 2.0);
  VFvectices[3] = glm::vec3(2.0, 0.0, 2.0);

  glm::vec3 Vcolors[6];
  Vcolors[0] = glm::vec3(1.0, 0.0, 1.0);
  Vcolors[1] = glm::vec3(1.0, 0.0, 1.0);
  Vcolors[2] = glm::vec3(1.0, 0.0, 1.0);
  Vcolors[3] = glm::vec3(1.0, 0.0, 1.0);

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Floor);
  glBindVertexArray(VAO_Floor);

  glGenBuffers(1, &VBO_Floor_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor_vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VFvectices), VFvectices, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_Floor_colors);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor_colors);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vcolors), Vcolors, GL_STATIC_DRAW);

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
