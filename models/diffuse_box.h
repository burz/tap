#pragma once

#include "gl_headers.h"
#include "drivers/shaders/diffuse.h"

class Diffuse_box : public Diffuse
{
public:
	Diffuse_box();
	Diffuse_box( float *position, float *forward, float *up, float *light_position, float *light_intensity, float *diffuse_reflectivity );

	virtual void load_vertices();

	virtual void draw();
private:
	static GLuint vertex_array;
};

