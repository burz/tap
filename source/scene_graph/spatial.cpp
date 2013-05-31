#include <cstring>

#include "spatial.h"
#include "scene_graph_node.h"
#include "math/math.h"

Spatial::Spatial()
{
	world_bound = 0;
	parent = 0;

	memcpy(local_transformation, Math::identity_matrix4, sizeof(float) * 16);
}

Spatial::Spatial(Scene_graph_node *parent, const float *local_transformation)
	: parent(parent)
{
	world_bound = 0;

	memcpy(this->local_transformation, local_transformation, sizeof(float) * 16);
}

Spatial::~Spatial()
{
	if(world_bound != 0)
		delete world_bound;
}

void Spatial::get_local_transformation(float *destination) const
{
	memcpy(destination, local_transformation, sizeof(float) * 16);
}

const float *Spatial::get_local_transformation() const
{
	return local_transformation;
}

void Spatial::get_world_transformation(float *destination) const
{
	memcpy(destination, world_transformation, sizeof(float) * 16);
}

const float *Spatial::get_world_transformation() const
{
	return world_transformation;
}

const Bounding_volume *Spatial::get_world_bound() const
{
	return world_bound;
}

