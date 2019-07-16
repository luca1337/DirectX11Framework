#pragma once

#include <PxPhysicsAPI.h>
#include <memory>

class PhysicsMaterial
{
public:
	PhysicsMaterial(float static_friction = 0.6f, float dynamic_friction = 0.6f, float bounciness = 0.1f);

	physx::PxMaterial* GetMaterial() const;

private:
	physx::PxMaterial* px_material;
};