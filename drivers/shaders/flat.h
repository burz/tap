#pragma once

#include "gl_headers.h"
#include "shader_driver.h"

class Flat : public Shader_driver
{
public:
	Flat();
	Flat(float *position, float *forward, float *up, float *color);

	virtual void load_shaders();
	virtual void load_vertices() = 0;

	virtual void load_uniforms();
	virtual void draw() = 0;

	void set_color(float *color);
protected:
	Vector3 color;

	static GLuint shader;
	static GLuint modelviewprojection_location;
	static GLuint color_location;
};

