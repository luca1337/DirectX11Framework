#pragma once

#include <PxPhysicsAPI.h>
#include <memory>

#include "Core.h"
#include <SimpleMath.h>

#include "Component.h"
#include "Enums.h"

class Actor;

class RigidBody : public Component
{
public:
	RigidBody(Actor& owner, float mass, float static_friction, float dynamic_friction, float restitution);
	std::shared_ptr<physx::PxBoxGeometry> CreateRigidBodyBoxGeometry();
	std::shared_ptr<physx::PxSphereGeometry> CreateRigidBodySphereGeometry(float radius);

	physx::PxShape* CreateShapeAndAttachGeometry(std::shared_ptr<physx::PxGeometry> geometry);

	void CreateDynamicBodyAndAttachShape(physx::PxShape* shape);
	void CreateStaticBodyAndAttachShape(physx::PxShape* shape);

	void AddForce(const DirectX::SimpleMath::Vector3 force, physx::PxForceMode::Enum force_mode);
	void SetKinematic(bool is_kinematic);
	void SetTrigger(bool is_trigger);
	void SetUseGravity(bool disable_gravity = false);
	void SetRigidBodyCCD(bool use_ccd);

	static unsigned int Type;

	virtual void Tick(float delta_time) override;

private:
	physx::PxMaterial* material;
	physx::PxRigidDynamic* body_dynamic;
	physx::PxRigidStatic* body_static;
	physx::PxRigidBody* current_body;
	physx::PxShape* shape;
	Actor& owner;

	float mass;
	float static_friction;
	float dynamic_friction;
	float restitution;

	float roll;
	float pitch;
	float yaw;
	float angle;
	physx::PxVec3 axis;
};
