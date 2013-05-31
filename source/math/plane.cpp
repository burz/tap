#include <cstring>

#include "plane.h"
#include "vectors.h"


Plane::Plane()
{
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	normal[0] = 1;
	normal[1] = 0;
	normal[2] = 0;
}

Plane::Plane(Vector3 position, Vector3 normal)
{
	set_position(position);
	set_normal(normal);
}

void Plane::set_position(Vector3 position)
{
	memcpy(this->position, position, sizeof(float) * 3);
}

void Plane::set_normal(Vector3 normal)
{
	memcpy(this->normal, normal, sizeof(float) * 3);

	Math::normalize(this->normal);
}

