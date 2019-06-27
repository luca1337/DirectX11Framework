#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(Actor& owner);

	virtual void Tick(float delta_time) override;

};