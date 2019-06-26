#include "Transform.h"

unsigned int Transform::Type = 0;

Transform::Transform()
{
	location = {};
	rotation = {};
	scale = { 1.0f, 1.0f, 1.0f };
}

void Transform::Translate(const SimpleMath::Vector3 & axis)
{
	location.x += axis.x;
	location.y += axis.y;
	location.z += axis.z;
}

void Transform::Translate(float x, float y, float z)
{
	location.x += x;
	location.y += y;
	location.z += z;
}

void Transform::Rotate(const SimpleMath::Vector3 & axis)
{
	rotation.x += axis.x;
	rotation.y += axis.y;
	rotation.z += axis.z;
}

void Transform::Rotate(float x, float y, float z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
}
