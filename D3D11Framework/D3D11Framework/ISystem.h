#pragma once

struct ISystem
{
	unsigned int update_offset;
	virtual void Update(float delta_time) = 0;
};