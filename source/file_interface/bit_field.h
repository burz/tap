#pragma once

#include "gl_headers.h"

void create_bit_field_file(const char *destination, unsigned short width,
                           unsigned short height, size_t type_size,
                           GLint internal_format, GLenum format, GLenum type, void *data);

void read_bit_field_file(const char *source, unsigned short *width,
                         unsigned short *height, size_t *type_size,
                         GLint *internal_format, GLenum *format, GLenum *type,
                         void **data);

