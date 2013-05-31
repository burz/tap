#include <cstring>
#include <cmath>

#include "camera.h"
#include "math/math.h"

float needed_radius(float left, float right, float bottom, float top, float near, float far);

Camera::Camera()
	: bounds(9.0)
{
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	Vector3 forward = { 0.0f, 0.0f, -1.0f };
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	set_position(position);
	set_forward(forward);
	set_up(up);

	Math::symmetric_perspective_projection(projection_matrix, 5.0f, 5.0f, 0.1f, 20.0f);
}

Camera::Camera(const Vector3 position, const Vector3 forward, const Vector3 up)
	: bounds(position, 9.0)
{
	set_position(position);
	set_forward(forward);
	set_up(up);

	Math::symmetric_perspective_projection(projection_matrix, 5.0f, 5.0f, 0.1f, 20.0f);
}

Camera::Camera(const Vector3 position, const Vector3 forward, const Vector3 up, float right, float top, float near, float far)
	: bounds(position, needed_radius(right, right, top, top, near, far))
{
	set_position(position);
	set_forward(forward);
	set_up(up);

	Math::symmetric_perspective_projection(projection_matrix, right, top, near, far);
}

Camera::Camera(float right, float top, float near, float far)
	: bounds(needed_radius(right, right, top, top, near, far))
{
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	Vector3 forward = { 0.0f, 0.0f, -1.0f };
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	set_position(position);
	set_forward(forward);
	set_up(up);

	Math::symmetric_perspective_projection(projection_matrix, right, top, near, far);
}

Camera::Camera(const Vector3 position, const Vector3 forward, const Vector3 up, float left, float right, float bottom, float top, float near, float far)
	: bounds(position, needed_radius(left, right, bottom, top, near, far))
{
	set_position(position);
	set_forward(forward);
	set_up(up);

	Math::perspective_projection(projection_matrix, left, right, bottom, top, near, far);
}

Camera::Camera(float left, float right, float bottom, float top, float near, float far)
	: bounds(needed_radius(left, right, bottom, top, near, far))
{
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	Vector3 forward = { 0.0f, 0.0f, -1.0f };
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	set_position(position);
	set_forward(forward);
	set_up(up);

	Math::perspective_projection(projection_matrix, left, right, bottom, top, near, far);
}

void Camera::set_position(const Vector3 position)
{
	memcpy(this->position, position, sizeof(float) * 3);

	bounds.set_position(position);
}

void Camera::set_forward(const Vector3 forward)
{
	memcpy(this->forward, forward, sizeof(float) * 3);

	Math::normalize(this->forward);
}

void Camera::set_up(const Vector3 up)
{
	memcpy(this->up, up, sizeof(float) * 3);

	Math::normalize(this->up);
}

void Camera::change_position(const Vector3 change)
{
	position[0] += change[0];
	position[1] += change[1];
	position[2] += change[2];

	bounds.change_position(change);
}

void Camera::change_position(float x, float y, float z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;

	bounds.change_position(x, y, z);
}

void Camera::get_view_matrix(Matrix4 destination) const
{
	Vector3 cross;

	Math::cross_product(cross, up, forward);

	Math::normalize(cross);

	destination[0] = cross[0];
	destination[1] = up[0];
	destination[2] = forward[0];
	destination[3] = 0.0f;
	destination[4] = cross[1];
	destination[5] = up[1];
	destination[6] = forward[1];
	destination[7] = 0.0f;
	destination[8] = cross[2];
	destination[9] = up[2];
	destination[10] = forward[2];
	destination[11] = 0.0f;
	destination[12] = -position[0] * cross[0] - position[1] * cross[1] - position[2] * cross[2];
	destination[13] = -position[0] * up[0] - position[1] * up[1] - position[2] * up[2];
	destination[14] = -position[0] * forward[0] - position[1] * forward[1] - position[2] * forward[2];
	destination[15] = 1.0f;
}

void Camera::get_projection_matrix(Matrix4 destination) const
{
	memcpy(destination, projection_matrix, sizeof(float) * 16);
}

bool Camera::is_culled(const Bounding_volume *volume) const
{
	return !bounds.test_volume_intersection(volume);
}

float needed_radius(float left, float right, float bottom, float top, float near, float far)
{
	return sqrt(fmax(left, right) * fmax(left, right) + fmax(bottom, top) * fmax(bottom, top) + fmax(near, far) * fmax(near, far));
}

