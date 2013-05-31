#include <cstring>

#include "matrix_stack.h"
#include "math/math.h"

Matrix_stack_node::Matrix_stack_node()
{
	next = 0;
}

Matrix_stack_node::Matrix_stack_node(const float *matrix, Matrix_stack_node *next)
{
	if(matrix == 0)
		matrix = Math::identity_matrix4;

	memcpy(this->matrix, matrix, sizeof(float) * 16);

	this->next = next;
}

Matrix_stack::Matrix_stack()
	: head(0, new Matrix_stack_node(Math::identity_matrix4, 0))
{
	size = 1;
}

Matrix_stack::~Matrix_stack()
{
	Matrix_stack_node *to_delete;

	while(head.next != 0) {
		to_delete = head.next;
		head.next = to_delete->next;

		delete to_delete;
	}
}

void Matrix_stack::push()
{
	Matrix_stack_node *new_node = new Matrix_stack_node(Math::identity_matrix4, head.next);

	head.next = new_node;

	size++;
}

void Matrix_stack::push_top()
{
	Matrix_stack_node *new_node = new Matrix_stack_node();
	memcpy(new_node->matrix, head.next->matrix, sizeof(float) * 16);
	
	new_node->next = head.next;

	head.next = new_node;

	size++;
}

void Matrix_stack::push_matrix(const Matrix4 matrix)
{
	Matrix_stack_node *new_node = new Matrix_stack_node(matrix, head.next);

	head.next = new_node;

	size++;
}

const float *Matrix_stack::top_matrix() const
{
	return head.next->matrix;
}

void Matrix_stack::pop()
{
	Matrix_stack_node *to_delete = head.next;

	head.next = to_delete->next;

	delete to_delete;

	size--;

	if(size == 0)
		push();
}

void Matrix_stack::push_right_product(const Matrix4 matrix)
{
	push();

	Math::multiply_matrices(head.next->matrix, head.next->next->matrix, matrix);
}

void Matrix_stack::push_left_product(const Matrix4 matrix)
{
	push();

	Math::multiply_matrices(head.next->matrix, matrix, head.next->next->matrix);
}

void Matrix_stack::right_multiply(const Matrix4 matrix)
{
	Matrix4 temp;

	memcpy(temp, head.next->matrix, sizeof(float) * 16);

	Math::multiply_matrices(head.next->matrix, temp, matrix);
}

void Matrix_stack::left_multiply(const Matrix4 matrix)
{
	Matrix4 temp;

	memcpy(temp, head.next->matrix, sizeof(float) * 16);

	Math::multiply_matrices(head.next->matrix, matrix, temp);
}

void Matrix_stack::scale(float factor)
{
	Math::scalar_multiply4(head.next->matrix, factor);
}

void Matrix_stack::translate(const Vector3 vector)
{
	Matrix4 matrix, result;

	Math::translate(matrix, vector);

	Math::multiply_matrices(result, head.next->matrix, matrix);

	memcpy(head.next->matrix, result, sizeof(float) * 16);
}

void Matrix_stack::translate(float x, float y, float z)
{
	Vector3 vector;
	Matrix4 matrix, result;

	vector[ 0 ] = x;
	vector[ 1 ] = y;
	vector[ 2 ] = z;

	Math::translate(matrix, vector);

	Math::multiply_matrices(result, head.next->matrix, matrix);

	memcpy(head.next->matrix, result, sizeof(float) * 16);
}

void Matrix_stack::rotate(float x_angle, float y_angle, float z_angle)
{
	Matrix4 rotation_matrix, temp;

	Math::xyz_rotate(rotation_matrix, x_angle, y_angle, z_angle);

	Math::multiply_matrices(temp, rotation_matrix, head.next->matrix);
	memcpy(head.next->matrix, temp, sizeof(float) * 16);
}

void Matrix_stack::perspective(float right, float top, float near, float far)
{
	Matrix4 matrix;

	Math::symmetric_perspective_projection(matrix, right, top, near, far);

	left_multiply(matrix);
}

void Matrix_stack::perspective(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4 matrix;

	Math::perspective_projection(matrix, left, right, bottom, top, near, far);

	left_multiply(matrix);
}

void Matrix_stack::get_normal_matrix(Matrix3 destination)
{
	Matrix3 matrix = { head.next->matrix[ 0 ], head.next->matrix[ 1 ], head.next->matrix[ 2 ],
					   head.next->matrix[ 4 ], head.next->matrix[ 5 ], head.next->matrix[ 6 ],
					   head.next->matrix[ 8 ], head.next->matrix[ 9 ], head.next->matrix[ 10 ] };

	Math::inverse(destination, matrix);
	Math::transpose3(destination);
}

