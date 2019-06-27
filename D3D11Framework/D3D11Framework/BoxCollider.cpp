#include "BoxCollider.h"

#include "Physix.h"
#include "Actor.h"
#include "Transform.h"

BoxCollider::BoxCollider(Actor& owner) : Collider(owner, DirectX::SimpleMath::Vector3(owner.transform->scale.x, owner.transform->scale.y, owner.transform->scale.z))
{
	physx::PxMaterial* physics_material = d3d_engine::Physix::Get().GetPxPhysics()->createMaterial(static_friction, dynamic_friction, bounciness);

	box_geometry = std::make_shared<physx::PxBoxGeometry>(physx::PxVec3(size.x, size.y, size.z) * half_extent_size);

	shape = d3d_engine::Physix::Get().GetPxPhysics()->createShape(*box_geometry, *physics_material);
}

void BoxCollider::Tick(float delta_time)
{
	// Call base tick
	Collider::Tick(delta_time);

	//.. logic
}
