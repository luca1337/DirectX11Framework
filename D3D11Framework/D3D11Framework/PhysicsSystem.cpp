#include "PhysicsSystem.h"

#include "Physics.h"

std::shared_ptr<PhysicsSystem> PhysicsSystem::Get()
{
	static std::shared_ptr<PhysicsSystem> ps = nullptr;

	if (!ps)
		ps = std::make_shared<PhysicsSystem>();

	return ps;
}

void PhysicsSystem::Update(float delta_time)
{
	Physics::Get().UpdatePhysx(delta_time);
}

void PhysicsSystem::Init()
{
	update_offset = 0;

	Physics& px = Physics::Get();
	px.InitPhysix();
}

PhysicsSystem::PhysicsSystem()
{

}
