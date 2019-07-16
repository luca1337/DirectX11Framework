#pragma once

#include "Component.h"

#include <memory>

#include "Core.h"
#include <SimpleMath.h>

#include "PxPhysicsAPI.h"

#include <vector>

class Actor;
class Mesh;

enum eColliderType
{
	eBOX,
	eSPHERE
};

class Collider : public Component
{
public:
	Collider(Actor& owner, eColliderType collider_type);
	Collider(Actor& owner, const float radius);

	static unsigned int Type;

	physx::PxShape* GetShape();

	eColliderType GetGeometryType();

	float GetRadius() const;

	virtual void Tick(float delta_time) override;

	virtual ~Collider() = 0;

protected:

	Actor& owner;
	
	// Physx variables
	std::shared_ptr<physx::PxBoxGeometry> box_geometry;
	std::shared_ptr<physx::PxSphereGeometry> sphere_geometry;
	physx::PxShape* shape;

	const float half_extent_size	= 0.5f;

	// Px physics material properties
	const float static_friction		= 0.6f;
	const float dynamic_friction	= 0.6f;
	const float bounciness			= 0.1f;
	float radius;

	std::vector<float> scales;

	// Mesh
	std::shared_ptr<Mesh> collider_mesh;
	eColliderType collider_type;
};