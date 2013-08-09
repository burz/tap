#include <cstdio>
#include <cstdlib>

#include "gl_headers.h"
#include "file_interface/vertex_data_file.h"

void test_vertex_data_file( const char *vertex_data_file );

int main( int argc, char *argv[] )
{
  test_vertex_data_file( argv[ 1 ] );

  return 0;
}

void test_vertex_data_file( const char *vertex_data_file )
{
  int number_of_arrays, number_of_vertices; 
  GLenum draw_mode;

  size_t *sizes;
  GLenum *types;
  int *components, *attribute_locations;

  void **data = read_vertex_data_file(vertex_data_file, &number_of_arrays,
                                      &number_of_vertices, &draw_mode, &sizes, &types,
                                      &components, &attribute_locations );

  printf( "Testing file: %s\n*************************************\n", vertex_data_file );
  printf( "Number of Arrays: %i\n", number_of_arrays );
  printf( "Number of Vertices: %i\n", number_of_vertices );
  printf( "Draw mode: %i\n\n", draw_mode );

  printf( "Sizes = { " );
  for( int i = 0; i < number_of_arrays; i++ )
    printf( "%lu, ", sizes[ i ] );
  printf( "\b\b }\n" );

  printf( "Types = { " );
  for( int i = 0; i < number_of_arrays; i++ )
    printf( "%i, ", types[ i ] );
  printf( "\b\b }\n" );

  printf( "Components = { " );
  for( int i = 0; i < number_of_arrays; i++ )
    printf( "%i, ", components[ i ] );
  printf( "\b\b }\n" );

  printf( "Attribute locations = { " );
  for( int i = 0; i < number_of_arrays; i++ )
    printf( "%i, ", attribute_locations[ i ] );
  printf( "\b\b }\n\n" ); 

  for( int i = 0; i < number_of_arrays; i++ ) {
    if( types[ i ] == GL_FLOAT ) {
      printf( "Data[ %i ] = { ", i );

      float **f_data = ( float ** ) data;

      for( int j = 0; j < number_of_vertices * components[ i ]; j++ )
          printf( "%f, ", f_data[ i ][ j ] );
      printf( "\b\b }\n" );
    }
    else
      printf( "Type %i is not known.\n", types[ i ] );
  }

  for( int i = 0; i < number_of_arrays; i++ )
    free( data[ i ] );
  free( data );
  free( sizes );
  free( types );
  free( components );
  free( attribute_locations );
}

