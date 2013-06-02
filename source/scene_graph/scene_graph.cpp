#include "scene_graph.h"

Scene_graph::Scene_graph()
  : head()
{
}

Scene_graph::~Scene_graph()
{
}

void Scene_graph::add(Geometry *geometry)
{
  int position = 0;

  while(position < head.number_of_children) {
    
  }

  head.add_child(geometry);
}

void Scene_graph::add(Scene_graph_node *node)
{
}

void Scene_graph::render(const Camera &camera)
{
  head.cull_and_draw(camera);
}

