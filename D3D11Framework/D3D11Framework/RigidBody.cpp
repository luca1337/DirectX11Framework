#include "RigidBody.h"
#include "Physix.h"
#include "Actor.h"
#include "Transform.h"
#include <cmath>

unsigned int RigidBody::Type = 0;

static void QuatToEuler(const physx::PxQuat& quat, float& rotx, float& roty, float& rotz)
{
	double sqw;
	double sqx;
	double sqy;
	double sqz;

	double rotxrad;
	double rotyrad;
	double rotzrad;

	sqw = quat.w * quat.w;
	sqx = quat.x * quat.x;
	sqy = quat.y * quat.y;
	sqz = quat.z * quat.z;

	rotxrad = (double)atan2l(2.0 * (quat.y * quat.z + quat.x * quat.w), (-sqx - sqy + sqz + sqw));
	rotyrad = (double)asinl(-2.0 * (quat.x * quat.z - quat.y * quat.w));
	rotzrad = (double)atan2l(2.0 * (quat.x * quat.y + quat.z * quat.w), (sqx - sqy - sqz + sqw));

	rotx = rotxrad;
	roty = rotyrad;
	rotz = rotzrad;

	return;
}

RigidBody::RigidBody(Actor& owner, float mass, float static_friction, float dynamic_friction, float restitution) : owner(owner)
{
	d3d_engine::Physix& physix = d3d_engine::Physix::Get();

	material = physix.GetPxPhysics()->createMaterial(static_friction, dynamic_friction, restitution);
	if (!material)
	{
		throw std::exception("unable to create material");
	}

	this->mass = mass;
	this->static_friction = static_friction;
	this->dynamic_friction = dynamic_friction;
	this->restitution = restitution;
}

std::shared_ptr<physx::PxBoxGeometry> RigidBody::CreateRigidBodyBoxGeometry()
{
	std::shared_ptr<physx::PxBoxGeometry> box_geometry = std::make_shared<physx::PxBoxGeometry>(physx::PxVec3(owner.transform->scale.x, owner.transform->scale.y, owner.transform->scale.z) * 0.5f);
	return box_geometry;
}

std::shared_ptr<physx::PxSphereGeometry> RigidBody::CreateRigidBodySphereGeometry(float radius)
{
	std::shared_ptr<physx::PxSphereGeometry> sphere_geometry = std::make_shared<physx::PxSphereGeometry>(radius);
	return sphere_geometry;
}

physx::PxShape* RigidBody::CreateShapeAndAttachGeometry(std::shared_ptr<physx::PxGeometry> geometry)
{
	shape = d3d_engine::Physix::Get().GetPxPhysics()->createShape(*geometry, *material, true);
	if (!shape)
	{
		throw std::exception("unable to create shape");
	}
	shape->userData = &owner;
	return shape;
}

void RigidBody::CreateDynamicBodyAndAttachShape(physx::PxShape* shape)
{
	body_dynamic = d3d_engine::Physix::Get().GetPxPhysics()->createRigidDynamic(physx::PxTransform(owner.transform->location.x, owner.transform->location.y, owner.transform->location.z));
	if (!body_dynamic)
	{
		throw std::exception("unable to create body_dynamic");
	}
	body_dynamic->setMass(mass);
	body_dynamic->attachShape(*shape);

	d3d_engine::Physix::Get().GetPxScene()->addActor(*body_dynamic);

	current_body = reinterpret_cast<physx::PxRigidBody*>(body_dynamic);
}

void RigidBody::CreateStaticBodyAndAttachShape(physx::PxShape* shape)
{
	body_static = d3d_engine::Physix::Get().GetPxPhysics()->createRigidStatic(physx::PxTransform(owner.transform->location.x, owner.transform->location.y, owner.transform->location.z));
	if (!body_static)
	{
		throw std::exception("unable to create body_static");
	}
	body_static->attachShape(*shape);

	d3d_engine::Physix::Get().GetPxScene()->addActor(*body_static);

	current_body = reinterpret_cast<physx::PxRigidBody*>(body_static);
}

void RigidBody::AddForce(const DirectX::SimpleMath::Vector3 force, physx::PxForceMode::Enum force_mode)
{
	body_dynamic->addForce(physx::PxVec3(force.x, force.y, force.z), force_mode);
}

void RigidBody::SetKinematic(bool is_kinematic)
{
	body_dynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, is_kinematic);
}

void RigidBody::SetTrigger(bool is_trigger)
{
	if (is_trigger)
	{
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	}
	else
	{
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
	}
}

void RigidBody::SetUseGravity(bool disable_gravity)
{
	shape->getActor()->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, disable_gravity);
}

void RigidBody::SetRigidBodyCCD(bool use_ccd)
{
	body_dynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, use_ccd);
}

void RigidBody::Tick(float delta_time)
{
	owner.transform->location.x = current_body->getGlobalPose().p.x;
	owner.transform->location.y = current_body->getGlobalPose().p.y;
	owner.transform->location.z = current_body->getGlobalPose().p.z;

	// Convert from quaternion to euler angles
	QuatToEuler(current_body->getGlobalPose().q, this->roll, this->pitch, this->yaw);
	
	owner.transform->rotation.x = this->roll;
	owner.transform->rotation.y = this->pitch;
	owner.transform->rotation.z = this->yaw;
}
