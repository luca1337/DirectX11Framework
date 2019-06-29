#include "SphereCollider.h"

#include "Physix.h"
#include "Actor.h"
#include "Transform.h"
#include "RigidBody.h"

SphereCollider::SphereCollider(Actor & owner) : Collider(owner, eColliderType::eSPHERE)
{
	physics_material = d3d_engine::Physix::Get().GetPxPhysics()->createMaterial(static_friction, dynamic_friction, bounciness);

	//todo: the radius MUST be correct here even if we update it on tick later
	sphere_geometry = std::make_shared<physx::PxSphereGeometry>(5);

	shape = d3d_engine::Physix::Get().GetPxPhysics()->createShape(*sphere_geometry, *physics_material, true);
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
