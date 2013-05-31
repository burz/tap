#pragma once

#include "spatial.h"
#include "renderer/camera.h"

class Scene_graph_node : public Spatial
{
	friend class Scene_graph;
public:
	Scene_graph_node();
	Scene_graph_node(Scene_graph_node *parent, const float *local_transformation);
	~Scene_graph_node();

	void add_child(Spatial *child);

	virtual void cull_and_draw(const Camera &camera) const;
private:
	int number_of_children;
	int capacity;

	Spatial **children;
};

