#pragma once

#include "ISystem.h"
#include <memory>

class PhysicsSystem final : public ISystem
{
public:
	static std::shared_ptr<PhysicsSystem> Get();

	virtual void Update(float delta_time) override;

	void Init();

	PhysicsSystem();
};