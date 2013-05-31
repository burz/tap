#pragma once

#include "gl_headers.h"
#include "shader_driver.h"

class Textured2 : public Shader_driver
{
public:
	Textured2();
	Textured2( float *position, float *forward, float *up );

	virtual void load_shaders();
	virtual void load_vertices() = 0;
	virtual void load_textures() = 0;

	virtual void load_uniforms();
	virtual void draw() = 0;
protected:
	static GLuint shader;
	static GLuint modelviewprojection_location;
	static GLuint texture_location;
};

