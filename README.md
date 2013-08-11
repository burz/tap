taps - An OpenGL based 3D game engine
=====================================

Author: Anthony Burzillo

******

tap is a 3D game engine I wrote during the summer of 2012. I started out programming the
basic math libraries and made it about as far as a naive scene graph.

# Executables

Currently tap only works on linux (Only tested on Ubuntu; OSX compiles but does not
display anything).

A particularly enlightening example is found in 
[programs/source/color_cube.cpp](programs/source/color_cube.cpp)
. This program renders a 3D cube using a perspective transformation. To run this program:

```shell
$ make color_cube
$ ./programs/color_cube
```
You can move the cube with the arrow as well as the 'o' and 'l' keys. Furthermore,
the cube can be rotated about the origin with the  'd', 'f', 'g', 'c', 'v', and 'b'
keys. The camera's position can be changed with the spacebar, and you may quit by
pressing ESC.

