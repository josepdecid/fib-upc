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
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Activem l'Array a pintar 
  glBindVertexArray(VAO_House);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
  // Desactivem el VAO
  glBindVertexArray(0);

  // Activem l'Array a pintar 
  glBindVertexArray(VAO_Tree);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  glViewport (0, 0, w, h);
}

void MyGLWidget::createBuffers ()
{
  glm::vec3 Color[5];  // Tres vèrtexs amb X, Y i Z
  
  Color[0] = glm::vec3(1.0, 0.0, 0.0);
  Color[1] = glm::vec3(0.0, 1.0, 0.0);
  Color[2] = glm::vec3(0.0, 0.0, 1.0);
  Color[3] = glm::vec3(1.0, 1.0, 0.0);
  Color[4] = glm::vec3(1.0, 0.0, 1.0);


  glm::vec3 VerticesHouse[5];  // Tres vèrtexs amb X, Y i Z

  VerticesHouse[0] = glm::vec3(-0.9, -1.0, 0.0);
  VerticesHouse[1] = glm::vec3(0.0, -1.0, 0.0);
  VerticesHouse[2] = glm::vec3(-0.9, 0.2, 0.0);
  VerticesHouse[3] = glm::vec3(0.0, 0.2, 0.0);
  VerticesHouse[4] = glm::vec3(-0.45, 0.5, 0.0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO_House);
  glBindVertexArray(VAO_House);

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO_House);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_House);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesHouse), VerticesHouse, GL_STATIC_DRAW);
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

  glm::vec3 VerticesTree[5];  // Tres vèrtexs amb X, Y i Z

  VerticesTree[0] = glm::vec3(0.4, -1.0, 0.0);
  VerticesTree[1] = glm::vec3(0.6, -1.0, 0.0);
  VerticesTree[2] = glm::vec3(0.4, 0.0, 0.0);
  VerticesTree[3] = glm::vec3(0.6, 0.0, 0.0);
  VerticesTree[4] = glm::vec3(0.5, 0.9, 0.0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO_Tree);
  glBindVertexArray(VAO_Tree);

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO_Tree);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Tree);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesTree), VerticesTree, GL_STATIC_DRAW);
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
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");
}
