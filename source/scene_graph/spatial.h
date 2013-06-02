#pragma once

#include "bounding_volumes/bounding_volume.h"
#include "renderer/camera.h"
#include "math/math.h"

class Scene_graph_node;

class Spatial
{
  friend class Scene_graph_node;
  friend class Scene_graph;
public:
  Spatial();
  Spatial(Scene_graph_node *parent, const float *local_transformation);
  ~Spatial();

  virtual void cull_and_draw(const Camera &camera) const = 0;

  void get_local_transformation(float *destination) const;
  const float *get_local_transformation() const;
  void get_world_transformation(float *destination) const;
  const float *get_world_transformation() const;
  const Bounding_volume *get_world_bound() const;
protected:
  Scene_graph_node *parent;

  Matrix4 local_transformation;
  Matrix4 world_transformation;

  Bounding_volume *world_bound;
};

