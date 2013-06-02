#include "transformations.h"
#include "matrices.h"

void Math::perspective_projection(Matrix4 destination, float left, float right, float bottom, float top, float near, float far)
{
  destination[0] = 2.0f * near / (right - left);
  destination[1] = 0.0f;
  destination[2] = 0.0f;
  destination[3] = 0.0f;
  destination[4] = 0.0f;
  destination[5] = 2.0f * near / (top - bottom); 
  destination[6] = 0.0f; 
  destination[7] = 0.0f; 
  destination[8] = (right + left) / (right - left);
  destination[9] = (top + bottom) / (top - bottom);
  destination[10] = - (far + near) / (far - near);
  destination[11] = -1.0f;
  destination[12] = 0.0f; 
  destination[13] = 0.0f; 
  destination[14] = -2.0f * far * near / (far - near);
  destination[15] = 0.0f; 

}

void Math::symmetric_perspective_projection(Matrix4 destination, float right, float top, float near, float far)
{
  destination[0] = near / right;
  destination[1] = 0.0f;
  destination[2] = 0.0f;
  destination[3] = 0.0f;
  destination[4] = 0.0f;
  destination[5] = near / top; 
  destination[6] = 0.0f; 
  destination[7] = 0.0f; 
  destination[8] = 0.0f; 
  destination[9] = 0.0f;
  destination[10] = - (far + near) / (far - near);
  destination[11] = -1.0f;
  destination[12] = 0.0f; 
  destination[13] = 0.0f; 
  destination[14] = -2.0f * far * near / (far - near);
  destination[15] = 0.0f; 
}

