#include "renderer.h"

Renderer::Renderer()
  : matrix_stack(), scene_graph()
{
}

void Renderer::render_frame(const Camera &camera)
{
  scene_graph.render(camera);
}

