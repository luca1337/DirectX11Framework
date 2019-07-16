#include "SphereCollider.h"

#include "Physics.h"
#include "Actor.h"
#include "Transform.h"
#include "RigidBody.h"
#include "PhysicsMaterial.h"

SphereCollider::SphereCollider(Actor & owner) : Collider(owner, eColliderType::eSPHERE)
{
	//todo: the radius MUST be correct here even if we update it on tick later
	sphere_geometry = std::make_shared<physx::PxSphereGeometry>(5.0f);

	shape = Physics::Get().GetPxPhysics()->createShape(*sphere_geometry, *Physics::Get().default_physics_material->GetMaterial(), true);
}

void SphereCollider::Tick(float delta_time)
{
	// Call base tick
	Collider::Tick(delta_time);

	auto rad = GetRadius();

	//.. logic
	physx::PxSphereGeometry sphere_g(rad);
	shape->setGeometry(sphere_g);
}
