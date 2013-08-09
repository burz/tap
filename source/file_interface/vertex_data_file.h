#pragma once

#include "gl_headers.h"

void create_vertex_data_file(const char *destination, int number_of_arrays,
                             int number_of_vertices, GLenum draw_mode, ...);

void create_vertex_data_file_arrays(const char *destination, int number_of_arrays,
                                    int number_of_vertices, GLenum draw_mode,
                                    size_t *sizes, GLenum *types, int *components,
                                    int *attribute_locations, void **data);

void **read_vertex_data_file(const char *vertex_data_file, int *number_of_arrays,
                             int *number_of_vertices, GLenum *draw_mode, size_t **sizes,
                             GLenum **types, int **components, int **attribute_locations);

