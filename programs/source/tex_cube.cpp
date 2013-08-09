#include <cstdio>
#include <cstdlib>

#include "gl_headers.h"
#include "renderer/shader_controller.h"
#include "renderer/matrix_stack.h"
#include "renderer/texture_controller.h"
#include "renderer/vao_controller.h"
#include "renderer/camera.h"
#include "math/math.h"
#include "models/textured2_box.h"

void keyboard_handler(unsigned char key, int x, int y);
void special_key_handler(int key, int x, int y);

Shader_controller shader_controller;
Texture_controller texture_controller;
VAO_controller vao_controller;

Matrix_stack modelview_stack;
Matrix_stack projection_stack;

Camera camera;

float position1[] = { 1.0f, 0.0f, 0.0f };
float forward1[] = { 1.0f, 0.0f, 0.0f };
float up1[] = { 0.0f, 1.0f, 0.0f };
float color1[] = { 1.0f, 0.0f, 0.0f, 1.0f };

float position2[] = { -1.0f, 0.0f, 0.0f };
float forward2[] = { -1.0f, 0.0f, 0.0f };
float up2[] = { 0.0f, -1.0f, 0.0f };
float color2[] = { 0.0f, 1.0f, 0.0f, 1.0f };

float position3[] = { 0.0f, 1.0f, 0.0f };
float forward3[] = { 0.0f, 1.0f, 0.0f };
float up3[] = { 1.0f, 0.0f, 0.0f };
float color3[] = { 0.0f, 0.0f, 1.0f, 1.0f };

float position4[] = { 0.0f, -1.0f, 0.0f };
float forward4[] = { 0.0f, -1.0f, 0.0f };
float up4[] = { 0.0f, 0.0f, 1.0f };
float color4[] = { 0.0f, 1.0f, 1.0f, 1.0f };

float position5[] = { 0.0f, 0.0f, 1.0f };
float forward5[] = { 0.0f, 0.0f, 1.0f };
float up5[] = { 0.0f, 1.0f, 0.0f };
float color5[] = { 1.0f, 1.0f, 0.0f, 1.0f };

float position6[] = { 0.0f, 0.0f, -1.0f };
float forward6[] = { 0.0f, 0.0f, -1.0f };
float up6[] = { 1.0f, 0.0f, 0.0f };
float color6[] = { 1.0f, 0.0f, 1.0f, 1.0f };

Textured2_box t1 (position1, forward1, up1);
Textured2_box t2 (position2, forward2, up2);
Textured2_box t3 (position3, forward3, up3);
Textured2_box t4 (position4, forward4, up4);
Textured2_box t5 (position5, forward5, up5);
Textured2_box t6 (position6, forward6, up6);

float position_c[] = { 4.0f, 0.0f, 0.0f };
float forward_c[] = { 4.0f, 0.0f, 0.0f };
float up_c[] = { 0.0f, 1.0f, 0.0f };

void start()
{
  t6.load_shaders();
  t6.load_vertices();

  t1.load_textures("data/textures/cube4092.bf");
  t2.load_textures("data/textures/scene20011.bf");
  t3.load_textures("data/textures/land.bf");
  t4.load_textures("data/textures/hello.bf");
  t5.load_textures("data/textures/lol.bf");
  t6.load_textures("data/textures/munan.bf");

  projection_stack.perspective(1.0f, 1.0f, 0.5f, 10.0f);

  camera.set_forward(forward_c);
  camera.set_position(position_c);
  camera.set_up(up_c);

  GLenum error;
  if((error = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "An error occured while starting: code %i\n", error);

    exit(1);
  }
}

void render_scene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Matrix4 matrix;
  camera.get_view_matrix(matrix);
  projection_stack.push_right_product(matrix);

  t1.get_model_matrix(matrix);
  modelview_stack.push_right_product(matrix);

  t1.draw();

  modelview_stack.pop();
  t2.get_model_matrix(matrix);
  modelview_stack.push_right_product(matrix);

  t2.draw();

  modelview_stack.pop();
  t3.get_model_matrix(matrix);
  modelview_stack.push_right_product(matrix);

  t3.draw();

  modelview_stack.pop();
  t4.get_model_matrix(matrix);
  modelview_stack.push_right_product(matrix);

  t4.draw();

  modelview_stack.pop();
  t5.get_model_matrix(matrix);
  modelview_stack.push_right_product(matrix);

  t5.draw();

  modelview_stack.pop();
  t6.get_model_matrix(matrix);
  modelview_stack.push_right_product(matrix);

  t6.draw();

  modelview_stack.pop();
  projection_stack.pop();

  glutSwapBuffers();

  GLenum error;
  if((error = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "An error occured while rendering: code %i\n", error);

    exit(1);
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(950, 950);
  glutCreateWindow("Cube");

  glutDisplayFunc(render_scene);
  glutKeyboardFunc(keyboard_handler);
  glutSpecialFunc(special_key_handler);

#ifndef __APPLE__
  GLenum err = glewInit();
  if(GLEW_OK != err) {
    fprintf(stderr, "Glew Error: %s",  glewGetErrorString(err));

    return 1;
  }
#endif

  start();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glutMainLoop();

  return 0;
}

int side = 2;

void keyboard_handler(unsigned char key, int x, int y)
{
  if(key == ' ') {
    if(++side > 6)
      side = 1;

    switch(side) {
      case 1: position_c[0] = 0.0f;
           position_c[1] = 0.0f;
           position_c[2] = 4.0f;
           forward_c[0] = 0.0f;
           forward_c[1] = 0.0f;
           forward_c[2] = 1.0f;
           up_c[0] = 0.0f;
           up_c[1] = 1.0f;
           up_c[2] = 0.0f;
           break;
      case 2: position_c[0] = 4.0f;
              position_c[1] = 0.0f;
              position_c[2] = 0.0f;
              forward_c[0] = 1.0f;
              forward_c[1] = 0.0f;
              forward_c[2] = 0.0f;
              up_c[0] = 0.0f;
              up_c[1] = 1.0f;
              up_c[2] = 0.0f;
              break;
      case 3: position_c[0] = 0.0f;
              position_c[1] = 0.0f;
              position_c[2] = -4.0f;
              forward_c[0] = 0.0f;
              forward_c[1] = 0.0f;
              forward_c[2] = -1.0f;
              up_c[0] = 0.0f;
              up_c[1] = 1.0f;
              up_c[2] = 0.0f;
              break;
      case 4: position_c[0] = 0.0f;
              position_c[1] = -4.0f;
              position_c[2] = 0.0f;
              forward_c[0] = 0.0f;
              forward_c[1] = -1.0f;
              forward_c[2] = 0.0f;
              up_c[0] = 0.0f;
              up_c[1] = 0.0f;
              up_c[2] = 1.0f;
              break;
      case 5: position_c[0] = 0.0f;
              position_c[1] = 4.0f;
              position_c[2] = 0.0f;
              forward_c[0] = 0.0f;
              forward_c[1] = 1.0f;
              forward_c[2] = 0.0f;
              up_c[0] = 0.0f;
              up_c[1] = 0.0f;
              up_c[2] = -1.0f;
              break;
      case 6: position_c[0] = 0.0f;
              position_c[1] = -4.0f;
              position_c[2] = 0.0f;
              forward_c[0] = 0.0f;
              forward_c[1] = -1.0f;
              forward_c[2] = 0.0f;
              up_c[0] = 0.0f;
              up_c[1] = 0.0f;
              up_c[2] = 1.0f;
              break;
      default: break;
    }

    camera.set_forward(forward_c);
    camera.set_position(position_c);
    camera.set_up(up_c);

    glutPostRedisplay();

    printf("updated; side: %i\n", side);
  }
  else if(key == 'c') {
    modelview_stack.rotate(0.2f, 0.0f, 0.0f);

    glutPostRedisplay();
  }
  else if(key == 'v') { 
    modelview_stack.rotate(0.0f, 0.2f, 0.0f);

    glutPostRedisplay();
  }
  else if(key == 'b') {
    modelview_stack.rotate(0.0f, 0.0f, 0.2f);

    glutPostRedisplay();
  }
  else if(key == 'd') {
    modelview_stack.rotate(-0.2f, 0.0f, 0.0f);

    glutPostRedisplay();
  }
  else if(key == 'f') { 
    modelview_stack.rotate(0.0f, -0.2f, 0.0f);

    glutPostRedisplay();
  }
  else if(key == 'g') {
    modelview_stack.rotate(0.0f, 0.0f, -0.2f);

    glutPostRedisplay();
  }
  else if(key == 'o') {
    modelview_stack.translate(0.0f, -0.01f, -1.0f);

    glutPostRedisplay();
  }
  else if(key == 'l') {
    modelview_stack.translate(0.0f, 0.0f, 1.0f);

    glutPostRedisplay();
  }
  else if(key == 0x1b)
    exit(0);
}

void special_key_handler(int key, int x, int y)
{
  if(key == GLUT_KEY_UP) {
    modelview_stack.translate(0.0f, 0.01f, 0.0f);

    glutPostRedisplay();
  }   
  else if(key == GLUT_KEY_DOWN) {
    modelview_stack.translate(0.0f, -0.01f, 0.0f);

    glutPostRedisplay();
  }
  else if(key == GLUT_KEY_LEFT) {
    modelview_stack.translate(-0.01f, 0.0f, 0.0f);

    glutPostRedisplay();
  }
  else if(key == GLUT_KEY_RIGHT) {
    modelview_stack.translate(0.01f, 0.0f, 0.0f);

    glutPostRedisplay();
  }
}

