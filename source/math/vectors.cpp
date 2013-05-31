#include <cmath>

#include "vectors.h"

float Math::abs(const Vector3 a, const Vector3 b)
{
	int sum = (a[0] - b[0]) * (a[0] - b[0]);
	sum += (a[1] - b[1]) * (a[1] - b[1]);
	sum += (a[2] - b[2]) * (a[2] - b[2]);

	return sqrt(sum);
}

float Math::length(const Vector3 vector)
{
	return sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

void Math::normalize(Vector3 vector)
{
	float length = Math::length(vector);

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

void Math::cross_product(Vector3 destination, const Vector3 a, const Vector3 b)
{
	destination[0] = a[1] * b[2] - a[2] * b[1];
	destination[1] = a[2] * b[0] - a[0] * b[2];
	destination[2] = a[0] * b[1] - a[1] * b[0];
}

