#pragma once

#include "renderer/renderer.h"

#define MAX_PROGRAM_NAME_LENGTH 32

class Program
{
public:
  Program();
  Program(char *name);
  Program(int window_length, int window_height);
  Program(char *name, int window_length, int window_height);

  void start();
  static void render_scene();
  int main(int argc, char *argv[]);

  static void keyboard_handler(unsigned char key, int x, int y);
  static void special_key_handler(int key, int x, int y);
protected:
  char name[MAX_PROGRAM_NAME_LENGTH];

  int window_width;
  int window_height;

  Renderer renderer;
};

