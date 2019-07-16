#include "BoxCollider.h"

#include "Physics.h"
#include "Actor.h"
#include "Transform.h"
#include "PhysicsMaterial.h"

BoxCollider::BoxCollider(Actor& owner) : Collider(owner, eColliderType::eBOX)
{
	box_geometry = std::make_shared<physx::PxBoxGeometry>(physx::PxVec3(owner.transform->scale.x, owner.transform->scale.y, owner.transform->scale.z) * half_extent_size);

	shape = Physics::Get().GetPxPhysics()->createShape(*box_geometry, *Physics::Get().default_physics_material->GetMaterial(), true);
}

void BoxCollider::Tick(float delta_time)
{
	// Call base tick
	Collider::Tick(delta_time);

	//.. logic if needed
}
