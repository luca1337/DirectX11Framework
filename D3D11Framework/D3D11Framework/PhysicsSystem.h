#pragma once

#include "ISystem.h"

class PhysicsSystem : public ISystem
{
public:
	static PhysicsSystem& Get();

	virtual void Update(float delta_time) override;

	void Init();
};