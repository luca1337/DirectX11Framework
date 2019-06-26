#pragma once

#include "Core.h"
#include <SimpleMath.h>
#include "Component.h"

using namespace DirectX;

class Transform : public Component
{
public:
	Transform();

	static unsigned int Type;

	SimpleMath::Vector3 location;
	SimpleMath::Vector3 rotation;
	SimpleMath::Vector3 scale;

	void Translate(const SimpleMath::Vector3& axis);
	void Translate(float x, float y, float z);

	void Rotate(const SimpleMath::Vector3& axis);
	void Rotate(float x, float y, float z);
};