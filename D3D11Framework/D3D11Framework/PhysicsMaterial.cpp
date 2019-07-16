#include "PhysicsMaterial.h"
#include "Physics.h"

PhysicsMaterial::PhysicsMaterial(float static_friction, float dynamic_friction, float bounciness)
{
	px_material = Physics::Get().GetPxPhysics()->createMaterial(static_cast<physx::PxReal>(static_friction), static_cast<physx::PxReal>(dynamic_friction), static_cast<physx::PxReal>(bounciness));
}

physx::PxMaterial* PhysicsMaterial::GetMaterial() const
{
	return px_material;
}
