#pragma once

#include "Component.h"

class Actor;

class RotatorComponent : public Component
{
public:
	RotatorComponent(Actor& owner);

	static unsigned int Type;

	virtual void Tick(float delta_time) override;

	bool bRotate;

private:
	Actor& owner;

};