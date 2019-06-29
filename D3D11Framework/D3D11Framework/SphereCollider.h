#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(Actor& owner);

	virtual void Tick(float delta_time) override;
};