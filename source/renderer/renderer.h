#include "camera.h"
#include "matrix_stack.h"
#include "shader_controller.h"
#include "texture_controller.h"
#include "vao_controller.h"
#include "scene_graph/scene_graph.h"

class Renderer
{
public:
	Renderer();

	void render_frame(const Camera &camera);
protected:
	Matrix_stack matrix_stack;
	Shader_controller shader_controller;
	Texture_controller texture_controller;
	VAO_controller vao_controller;
	Scene_graph scene_graph;
};

