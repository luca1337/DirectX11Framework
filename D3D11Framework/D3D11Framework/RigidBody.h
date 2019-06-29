#pragma once

#include <PxPhysicsAPI.h>
#include <memory>

#include "Core.h"
#include <SimpleMath.h>

#include "Component.h"
#include "Enums.h"

class Actor;

enum eRigidBodyType
{
	DYNAMIC,
	STATIC
};

enum eGeometryType
{
	BOX,
	SPHERE
};

class RigidBody : public Component
{
public:
	RigidBody(Actor& owner, float mass, eRigidBodyType rb_type = eRigidBodyType::DYNAMIC);

	void AddForce(const DirectX::SimpleMath::Vector3 force, physx::PxForceMode::Enum force_mode);
	void SetKinematic(bool is_kinematic);
	void SetTrigger(bool is_trigger);
	void SetUseGravity(bool disable_gravity = false);
	void SetRigidBodyCCD(bool use_ccd);
	void SetRotation(float x, float y, float z);
	float GetDensity() const;

	static unsigned int Type;

	virtual void Tick(float delta_time) override;

	physx::PxRigidDynamic* body_dynamic;
	physx::PxRigidBody* current_body;
	physx::PxRigidStatic* body_static;
private:
	physx::PxMaterial* material;
	physx::PxShape* shape;
	Actor& owner;
	eRigidBodyType current_type;
	eGeometryType geometry_type;

	float mass;
	float static_friction;
	float dynamic_friction;
	float restitution;
	float volume;
	float density;
	float current_density;

	float roll;
	float pitch;
	float yaw;
	float angle;
	physx::PxVec3 axis;
};
