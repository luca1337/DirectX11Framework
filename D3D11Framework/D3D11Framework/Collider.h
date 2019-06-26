#pragma once

#include <PxPhysicsAPI.h>
#include <memory>

#include "Component.h"

#include "Core.h"
#include <SimpleMath.h>

#include "RigidBody.h"
#include "Actor.h"
#include "Physix.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "ShaderManager.h"
#include "Engine.h"

#include "Mesh.h"

class Collider : public Component
{
public:
	Collider(Actor& owner, const DirectX::SimpleMath::Vector3& size);
	Collider(Actor& owner, const float radius);

	static unsigned int Type;

	virtual void Tick(float delta_time) override;

	virtual ~Collider() = 0;

protected:

	physx::PxVec3 size;
	float radius;
	
	// Physx variables
	std::shared_ptr<physx::PxBoxGeometry> box_geometry;
	std::shared_ptr<physx::PxSphereGeometry> sphere_geometry;
	physx::PxMaterial* physics_material;
	physx::PxShape* shape;

	const float half_extent_size	= 0.5f;

	// Px physics material properties
	const float static_friction		= 0.6f;
	const float dynamic_friction	= 0.6f;
	const float bounciness			= 0.9f;

	// Mesh
	std::shared_ptr<Mesh> collider_mesh;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(Actor& owner, const DirectX::SimpleMath::Vector3& size) : Collider(owner, size)
	{
		physx::PxMaterial* physics_material = d3d_engine::Physix::Get().GetPxPhysics()->createMaterial(static_friction, dynamic_friction, bounciness);

		box_geometry = std::make_shared<physx::PxBoxGeometry>(physx::PxVec3(size.x, size.y, size.z) * half_extent_size);

		shape = d3d_engine::Physix::Get().GetPxPhysics()->createShape(*box_geometry, *physics_material);
	}

	virtual void Tick(float delta_time) override
	{
		// Call base tick
		Collider::Tick(delta_time);

		//.. logic
	}

};

class SphereCollider : public Collider
{
public:
	SphereCollider(Actor& owner, const float radius) : Collider(owner, radius)
	{
		physx::PxMaterial* physics_material = d3d_engine::Physix::Get().GetPxPhysics()->createMaterial(static_friction, dynamic_friction, bounciness);

		sphere_geometry = std::make_shared<physx::PxSphereGeometry>(radius);

		shape = d3d_engine::Physix::Get().GetPxPhysics()->createShape(*sphere_geometry, *physics_material);
	}

	virtual void Tick(float delta_time) override
	{
		// Call base tick
		Collider::Tick(delta_time);

		//.. logic
	}
};