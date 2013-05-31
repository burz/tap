#include "textured2_box.h"
#include "renderer/vao_controller.h"
#include "renderer/matrix_stack.h"
#include "renderer/texture_controller.h"

extern VAO_controller vao_controller;
extern Matrix_stack modelview_stack;
extern Texture_controller texture_controller;

GLuint Textured2_box::vertex_array = 0;

Textured2_box::Textured2_box()
{
}

Textured2_box::Textured2_box(float *position, float *forward, float *up)
	: Textured2(position, forward, up)
{
}

Textured2_box::Textured2_box(float *position, float *forward, float *up, const char *file)
	: Textured2(position, forward, up)
{
	texture = texture_controller.load_texture2(file, GL_NEAREST, GL_NEAREST, GL_CLAMP);
}

void Textured2_box::load_vertices()
{
	if(vertex_array != 0)
		return;

	vertex_array = vao_controller.create_vertex_array("data/arrays/textured2_box.vdf");
}

void Textured2_box::load_textures()
{
	texture = texture_controller.load_texture2("data/textures/scene20011.bf", GL_NEAREST, GL_NEAREST, GL_CLAMP);
}

void Textured2_box::load_textures(const char *file)
{
	texture = texture_controller.load_texture2(file, GL_NEAREST, GL_NEAREST, GL_CLAMP);
}

void Textured2_box::draw()
{
	modelview_stack.push_top();

	glUseProgram(shader);

	load_uniforms();

	glUniform1i(texture_location, texture);

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

