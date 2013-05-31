#include <cstring>
#include <cstdlib>

#include "gl_headers.h"
#include "program.h"

#define DEFAULT_WINDOW_SIZE 950

const char default_name[] = "Program";

Program::Program()
{
	strcpy(name, default_name);

	window_width = DEFAULT_WINDOW_SIZE;
	window_height = DEFAULT_WINDOW_SIZE;
}

Program::Program(char *name)
{
	strcpy(this->name, name);

	window_width = DEFAULT_WINDOW_SIZE;
	window_height = DEFAULT_WINDOW_SIZE;
}

Program::Program(int window_width, int window_height)
{
	strcpy(name, default_name);

	this->window_width = window_width;
	this->window_height = window_height;
}

Program::Program(char *name, int window_width, int window_height)
{
	strcpy(this->name, name);

	this->window_width = window_width;
	this->window_height = window_height;
}

void Program::start()
{
}

void Program::render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

int Program::main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow(name);

	glutDisplayFunc(&render_scene);
	glutKeyboardFunc(&keyboard_handler);
	glutSpecialFunc(&special_key_handler);

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

void Program::keyboard_handler(unsigned char key, int x, int y)
{
	if(key == 0x1b)
		exit(0);
}

void Program::special_key_handler(int key, int x, int y)
{
}

