#pragma once

#include "gl_headers.h"
#include "drivers/shaders/textured2.h"

class Textured2_box : public Textured2
{
public:
	Textured2_box();
	Textured2_box( float *position, float *forward, float *up );
	Textured2_box( float *position, float *forward, float *up, const char *file );

	virtual void load_vertices();
	virtual void load_textures();
	void load_textures( const char *file );

	virtual void draw();
private:
	static GLuint vertex_array;

	GLenum texture;
};

