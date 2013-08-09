#pragma once

#include <cstdio>

#include "gl_headers.h"
#include "structures/queue.h"
#include "structures/hash_table.h"

typedef struct {
  GLenum location;
  int number_of_textures;
  GLuint *textures;
} texture_record;

class Texture_controller
{
public:
  Texture_controller();
  ~Texture_controller();

  GLenum load_texture2(const char *file, GLenum min_filter, GLenum mag_filter,
                       GLenum wrap_mode);

  void delete_texture(const char *file);

  GLenum get_free_texture();
private:
  GLenum next_free_texture;
  Queue<GLenum> free_textures;

  Hash_table<const char*, texture_record> loaded_files;
};

