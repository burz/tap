CC = g++
CFLAGS = -c -g

OPSYS = $(shell uname)

ifeq ($(OPSYS), Windows_NT)
	GL_LIBS = -l GL -l glut -l GLEW
else
	ifeq ($(OPSYS), Linux)
		GL_LIBS = -l GL -l glut -l GLEW
	else
		GL_LIBS = -framework OpenGL -framework GLUT
	endif
endif

VPATH = source
INCL = -I source/ -I ./ -I lib/

all:	main programs utilities

main:	main.o render
		  $(CC) -o main $< $(RENDER) $(GL_LIBS)

VPATH += programs/source
programs: color_cube tex_cube box move

color_cube:	color_cube.o render models
			$(CC) -o programs/color_cube $< $(RENDER) $(MODELS) $(GL_LIBS)

tex_cube:	tex_cube.o render models
			$(CC) -o programs/tex_cube $< $(RENDER) $(MODELS) $(GL_LIBS)

box:		box.o render models
			$(CC) -o programs/box $< $(RENDER) $(MODELS) $(GL_LIBS)

move:		move.o prgrm models
			$(CC) -o programs/move $< $(PRGRM) $(MODELS) $(GL_LIBS)

VPATH += source/math
MATH = vectors.o matrices.o plane.o transformations.o
math: $(MATH)

VPATH += source/structures
STRUCTURES = hash_functions.o compare_to.o
structures: $(STRUCTURES)

VPATH += source/file_interface
FILEINT = vertex_data_file.o bit_field.o array_data_file.o
fileint: $(FILEINT)

VPATH += source/bounding_volumes
BNDVOLM = $(MATH) bounding_volume.o bounding_sphere.o
bndvolm: $(BNDVOLM)

VPATH += source/scene_graph
SCNGRPH = $(BNDVOLM) scene_graph_node.o spatial.o geometry.o scene_graph.o
scngrph: $(SCNGRPH)

VPATH += source/renderer
RENDER = $(STRUCTURES) $(SCNGRPH) $(FILEINT) frame.o camera.o matrix_stack.o \
		 renderer.o vao_controller.o texture_controller.o shader_controller.o
render: $(RENDER)

PRGRM = $(RENDER) program.o
prgrm: $(PRGRM)

VPATH += drivers/shaders
DRVSHDR = diffuse.o flat.o textured2.o
drvshdr: $(DRVSHDR)

VPATH += models
MODELS = $(DRVSHDR) diffuse_box.o diffuse_cube.o flat_box.o flat_cube.o textured2_box.o
models: $(MODELS)

VPATH += util/source
utilities:			test_texture test_vertex_data

test_texture:		test_texture.o fileint
					$(CC) -o util/test_texture $< $(FILEINT)

test_vertex_data:	test_vertex_data.o fileint
					$(CC) -o util/test_vertex_data $< $(FILEINT)

clean:
		rm -f *.o

%.o:	%.cpp
		$(CC) $(CFLAGS) $^ $(INCL)

