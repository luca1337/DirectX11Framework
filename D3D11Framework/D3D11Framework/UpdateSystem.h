#pragma once

#include "ISystem.h"

class UpdateSystem : public ISystem
{
public:
	virtual void Update(float delta_time) override;

};