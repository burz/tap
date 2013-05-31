#include <cstring>

#include "flat.h"
#include "math/math.h"
#include "renderer/shader_controller.h"
#include "renderer/matrix_stack.h"

extern Shader_controller shader_controller;

extern Matrix_stack modelview_stack;
extern Matrix_stack projection_stack;

GLuint Flat::shader = 0;
GLuint Flat::modelviewprojection_location = 0;
GLuint Flat::color_location = 0;

Flat::Flat()
{
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
}

Flat::Flat(float *position, float *forward, float *up, float *color)
	: Shader_driver(position, forward, up)
{
	memcpy(this->color, color, sizeof(float) * 4);
}

void Flat::load_shaders()
{
	if(shader != 0)
		return;

	shader = shader_controller.load_shaders_from_file("data/shaders/flat.vp", "data/shaders/flat.fp");

	glBindAttribLocation(shader, 0, "position");

	modelviewprojection_location = glGetUniformLocation(shader, "modelviewprojection_matrix");
	color_location = glGetUniformLocation(shader, "color");
}

void Flat::load_uniforms()
{
	Matrix4 modelviewprojection_matrix;

	Math::multiply_matrices(modelviewprojection_matrix, projection_stack.top_matrix(), modelview_stack.top_matrix());

	glUniformMatrix4fv(modelviewprojection_location, 1, GL_FALSE, modelviewprojection_matrix);

	glUniform4fv(color_location, 1, color);
}

void Flat::set_color(float *color)
{
	memcpy(this->color, color, sizeof(float) * 4);
}

