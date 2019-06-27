#include "SphereCollider.h"

#include "Physix.h"
#include "Actor.h"
#include "Transform.h"

SphereCollider::SphereCollider(Actor & owner, const float radius) : Collider(owner, radius)
{
	physx::PxMaterial* physics_material = d3d_engine::Physix::Get().GetPxPhysics()->createMaterial(static_friction, dynamic_friction, bounciness);

	sphere_geometry = std::make_shared<physx::PxSphereGeometry>(radius);

	shape = d3d_engine::Physix::Get().GetPxPhysics()->createShape(*sphere_geometry, *physics_material);
}

void SphereCollider::Tick(float delta_time)
{
	// Call base tick
	Collider::Tick(delta_time);

	//.. logic
}
