#pragma once

#include "gl_headers.h"

void create_array_data_file(const char *destination, const void *data, int number_of_vertices, size_t size, GLenum type, int components);

void read_array_data_file(const char *source, void **data, int *number_of_vertices, size_t *size, GLenum *type, int *components);

// each array_data file entered as: ... int attribute_location, const char *file, ...
void create_VDF_from_ADFs(const char *destination, int number_of_arrays, GLenum draw_mode, ...);

