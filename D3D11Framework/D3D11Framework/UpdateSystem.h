#pragma once

#include "ISystem.h"

class UpdateSystem : public ISystem
{
public:
	UpdateSystem();

	virtual void Update(float delta_time) override;

};