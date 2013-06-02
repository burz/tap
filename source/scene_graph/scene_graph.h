#pragma once

#include "scene_graph_node.h"
#include "geometry.h"
#include "renderer/camera.h"

class Scene_graph
{
public:
  Scene_graph();
  ~Scene_graph();

  void add(Geometry *geometry);
  void add(Scene_graph_node *node);

  void render(const Camera &camera);
private:
  Scene_graph_node head;
};

