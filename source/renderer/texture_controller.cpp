#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "texture_controller.h"
#include "file_interface/bit_field.h"
#include "structures/hash_functions.h"
#include "structures/compare_to.h"

#ifndef __APPLE__
#include <GL/glx.h>

PFNGLACTIVETEXTUREPROC glActiveTexture = 0;
#endif

Texture_controller::Texture_controller()
  : loaded_files(file_hash, string_compare_to)
{
  next_free_texture = 0;

#ifndef __APPLE__
  glActiveTexture = (PFNGLACTIVETEXTUREPROC) glXGetProcAddress((const GLubyte *) "glActiveTexture");
#endif

  if(glActiveTexture == NULL)  {
    fprintf(stderr, "glActiveTexture is NULL\n");

    exit(1);
  }
}

Texture_controller::~Texture_controller()
{
  Hash_table_iterator<const char*, texture_record> iterator = loaded_files.get_iterator();

  texture_record record;

  while(iterator.has_next())  {
    iterator.next(&record);

    glDeleteTextures(record.number_of_textures, record.textures);

    free(record.textures);

    free_textures.enqueue(record.location);
  }
}

GLenum Texture_controller::load_texture2(const char *file, GLenum min_filter, GLenum mag_filter, GLenum wrap_mode)
{
  texture_record record;

  if(loaded_files.get(file, &record))
    return record.location;

  unsigned short width, height;
  GLint internal_format;
  GLenum format, type;

  void *data;

  read_bit_field_file(file, &width, &height, NULL, &internal_format, &format, &type, &data);

  GLenum error;
    if((error = glGetError()) != GL_NO_ERROR)  {
        fprintf(stderr, "An error occured before active texture: code %i\n", error);

        exit(1);
    }

  GLenum texture_location;

  texture_location = get_free_texture();

  glActiveTexture(texture_location + GL_TEXTURE0);

  record.location = texture_location;
  record.number_of_textures = 1;
  record.textures = new GLuint;

  glGenTextures(1, record.textures);

  glBindTexture(GL_TEXTURE_2D, *record.textures);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);

  free(data);

  if(min_filter == GL_LINEAR_MIPMAP_LINEAR || min_filter == GL_LINEAR_MIPMAP_NEAREST || min_filter == GL_NEAREST_MIPMAP_LINEAR || min_filter == GL_NEAREST_MIPMAP_NEAREST)
    glGenerateMipmap(GL_TEXTURE_2D);

  loaded_files.add(file, record);

  return texture_location;
}

void Texture_controller::delete_texture(const char *file)
{
  texture_record record;

  if(!loaded_files.get(file, &record))
    return;

  loaded_files.remove(file);

  glDeleteTextures(record.number_of_textures, record.textures);

  free(record.textures);

  free_textures.enqueue(record.location);
}

GLenum Texture_controller::get_free_texture()
{
  if(!free_textures.is_empty())  {
    GLenum texture;

    free_textures.dequeue(&texture);

    return texture;
  }

  return next_free_texture++;
}

