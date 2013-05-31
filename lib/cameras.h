#pragma once

#include "renderer/camera.h"
#include "math/math.h"

const Vector3 plus_x = { 1.0, 0.0, 0.0 };
const Vector3 neg_x = { -1.0, 0.0, 0.0 };
const Vector3 plus_y = { 0.0, 1.0, 0.0 };
const Vector3 neg_y = { 0.0, -1.0, 0.0 };
const Vector3 plus_z = { 0.0, 0.0, 1.0 };
const Vector3 neg_z = { 0.0, 0.0, -1.0 };

namespace Cameras
{
	const Camera plus_x_camera(plus_x, neg_x, plus_y);
	const Camera neg_x_camera(neg_x, plus_x, plus_y);
	const Camera plus_y_camera(plus_y, neg_y, plus_z);
	const Camera neg_y_camera(neg_y, plus_y, neg_z);
	const Camera plus_z_camera(plus_z, neg_z, plus_y);
	const Camera neg_z_camera(neg_z, plus_z, plus_y);
}

