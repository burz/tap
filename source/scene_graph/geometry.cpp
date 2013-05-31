#include "geometry.h"

void Geometry::update_bounds()
{
	world_bound = model_bound;

	world_bound->transform_by(world_transformation);
}

void Geometry::cull_and_draw(const Camera &camera) const
{
	if(!camera.is_culled(world_bound))
		draw(camera);
}

