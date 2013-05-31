#pragma once

#include "spatial.h"
#include "bounding_volumes/bounding_volume.h"
#include "renderer/camera.h"

class Geometry : public Spatial
{
	friend class Scene_graph;
public:
	virtual void load_resources() = 0;

	void update_bounds();

	virtual void cull_and_draw(const Camera &camera) const;
	virtual void draw(const Camera &camera) const = 0;
protected:
	Bounding_volume *model_bound;
};

