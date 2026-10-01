#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
  rotation = 0;
  ra = 1.0;
  fov = fovi = (float) M_PI / 2.0;
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
  m.load("../../models/HomerProves.obj");

  carregaShaders();
  createBuffers();

  projectTransform();
  viewTransform();

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

  // Carreguem la transformació del model
  modelTransformFloor ();

  glBindVertexArray (VAO_Floor);
  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransform ()
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(scale));
  transform = glm::rotate(transform, rotation * float(M_PI / 4.0), glm::vec3(0, 1, 0));
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
  glm::mat4 Proj = glm::perspective(fov, ra, 0.4f, 3.0f);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
  //glm::lookAt(OBS, VRP, UP)
  glm::mat4 View = glm::lookAt(
    glm::vec3(0, 0, 1),
    glm::vec3(0, 0, 0),
    glm::vec3(0, 1, 0)
  );
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
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
  glm::vec3 Floor[6];  // Tres vèrtexs amb X, Y i Z
  Floor[0] = glm::vec3(-2.0, -1.0, 2.0);
  Floor[1] = glm::vec3(2.0, -1.0, 2.0);
  Floor[2] = glm::vec3(-2.0, -1.0, -2.0);
  Floor[3] = glm::vec3(2.0, -1.0, 2.0);
  Floor[4] = glm::vec3(2.0, -1.0, -2.0);
  Floor[5] = glm::vec3(-2.0, -1.0, -2.0);

  glm::vec3 Color[6];
  Color[0] = glm::vec3(1.0, 0.0, 0.0);
  Color[1] = glm::vec3(0.0, 0.0, 0.0);
  Color[2] = glm::vec3(0.0, 1.0, 0.0);
  Color[3] = glm::vec3(0.0, 0.0, 1.0);
  Color[4] = glm::vec3(1.0, 0.0, 1.0);
  Color[5] = glm::vec3(1.0, 1.0, 0.0);

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

  // FLOOR

  glGenVertexArrays(1, &VAO_Floor);
  glBindVertexArray(VAO_Floor);

  glGenBuffers(1, &VBO_Floor);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Floor), Floor, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_Floor_color);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor_color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);

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
