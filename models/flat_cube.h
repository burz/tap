#pragma once

#include "gl_headers.h"
#include "drivers/shaders/flat.h"

class Flat_cube : public Flat
{
public:
	Flat_cube( float *position, float *forward, float *up, float *color );

	virtual void load_vertices();

	virtual void draw();
private:
	static GLuint vertex_array;
};

