#include "PhysicsSystem.h"

PhysicsSystem& PhysicsSystem::Get()
{
	static PhysicsSystem* ps = nullptr;

	if (!ps)
		ps = new PhysicsSystem();

	return *ps;
}

void PhysicsSystem::Update(float delta_time)
{
}

void PhysicsSystem::Init()
{
	update_offset = 0;
}
