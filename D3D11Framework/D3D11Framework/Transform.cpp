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

void Transform::Rotate(const SimpleMath::Vector3 & eulers)
{
	// TODO: build rotation using Quaternions
	DirectX::SimpleMath::Quaternion new_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(eulers.x, eulers.y, eulers.z);
	rotation *= new_rotation;
}

void Transform::Rotate(float x, float y, float z)
{
	// TODO: build rotation using Quaternions
	DirectX::SimpleMath::Quaternion new_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(x, y, z);
	rotation *= new_rotation;
}
