#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(Actor& owner, const float radius);

	virtual void Tick(float delta_time) override;
};