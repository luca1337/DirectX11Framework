#pragma once

class Component
{
public:
	Component();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);

	bool Enabled;

	unsigned int ComponentType;
};