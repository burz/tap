#include "flat_box.h"
#include "renderer/vao_controller.h"
#include "renderer/matrix_stack.h"

extern VAO_controller vao_controller;

extern Matrix_stack modelview_stack;

GLuint Flat_box::vertex_array = 0;

Flat_box::Flat_box()
{
}

Flat_box::Flat_box(float *position, float *forward, float *up, float *color)
	: Flat(position, forward, up, color)
{
}

void Flat_box::load_vertices()
{
	if(vertex_array != 0)
		return;

	vertex_array = vao_controller.create_vertex_array("data/arrays/box.vdf");
}

void Flat_box::draw()
{
	modelview_stack.push_top();

	glUseProgram(shader);

	load_uniforms();

#ifdef __APPLE__
	glBindVertexArrayAPPLE(vertex_array);
#else
	glBindVertexArray(vertex_array);
#endif

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
#else
	glBindVertexArray(0);
#endif

	modelview_stack.pop();
}

