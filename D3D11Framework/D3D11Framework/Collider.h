#pragma once

#include "Component.h"

#include <memory>

#include "Core.h"
#include <SimpleMath.h>

#include "PxPhysicsAPI.h"

class Actor;
class Mesh;

class Collider : public Component
{
public:
	Collider(Actor& owner);
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