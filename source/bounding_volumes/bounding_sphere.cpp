#include "bounding_sphere.h"
#include "math/math.h"

Bounding_sphere::Bounding_sphere()
	: Bounding_volume()
{
	radius = 1;
}

Bounding_sphere::Bounding_sphere(Vector3 position)
	: Bounding_volume(position)
{
	radius = 1;
}

Bounding_sphere::Bounding_sphere(float radius)
	: Bounding_volume()
{
	this->radius = radius;
}

Bounding_sphere::Bounding_sphere(const Vector3 position, float radius)
	: Bounding_volume(position)
{
	this->radius = radius;
}

bool Bounding_sphere::test_volume_intersection(const Bounding_volume *volume) const
{
	if(Math::abs(position, volume->get_position()) <= radius + ((Bounding_sphere *) volume)->radius)
		return true;
	else
		return false;
}

bool Bounding_sphere::grow_to_contain(const Bounding_volume *volume)
{
	float new_radius = Math::abs(position, volume->get_position()) + ((Bounding_sphere *) volume)->radius;

	if(new_radius > radius) {
		radius = new_radius;

		return true;
	} else
		return false;
}

void Bounding_sphere::transform_by(const Matrix4 transformation)
{
}

