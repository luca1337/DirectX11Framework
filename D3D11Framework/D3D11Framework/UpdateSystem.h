#pragma once

#include "ISystem.h"
#include <memory>

class UpdateSystem final : public ISystem
{
public:
	UpdateSystem();

	virtual void Update(float delta_time) override;

};