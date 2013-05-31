#include <cstring>

#include "scene_graph_node.h"

#define DEFAULT_CAPACITY 4

Scene_graph_node::Scene_graph_node()
{
	number_of_children = 0;

	children = new Spatial*[DEFAULT_CAPACITY];

	capacity = DEFAULT_CAPACITY;
}

Scene_graph_node::Scene_graph_node(Scene_graph_node *parent, const float *local_transformation)
	: Spatial(parent, local_transformation)
{
	number_of_children = 0;

	children = new Spatial*[DEFAULT_CAPACITY];

	capacity = DEFAULT_CAPACITY;
}

Scene_graph_node::~Scene_graph_node()
{
	delete [] children;
}

void Scene_graph_node::add_child(Spatial *child)
{
	if(number_of_children == capacity) {
		Spatial **temp = children;

		capacity *= 2;

		children = new Spatial*[capacity];

		memcpy(children, temp, sizeof(Spatial *) * number_of_children);

		delete [] temp;
	}

	children[number_of_children++] = child;

	world_bound->grow_to_contain(child->world_bound);
}

void Scene_graph_node::cull_and_draw(const Camera &camera) const
{
	if(camera.is_culled(world_bound))
		return;

	for(int i = 0; i < number_of_children; i++)
		children[i]->cull_and_draw(camera);
}

