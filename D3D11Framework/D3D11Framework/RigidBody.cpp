#include "RigidBody.h"
#include "Physics.h"
#include "Actor.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

unsigned int RigidBody::Type = 0;

static physx::PxQuat EulerToQuat(float yaw, float pitch, float roll) // yaw (Z), pitch (Y), roll (X)
{
	// Abbreviations for the various angular functions
	float cy = (float)cos((float)yaw * 0.5);
	float sy = (float)sin((float)yaw * 0.5);
	float cp = (float)cos((float)pitch * 0.5);
	float sp = (float)sin((float)pitch * 0.5);
	float cr = (float)cos((float)roll * 0.5);
	float sr = (float)sin((float)roll * 0.5);

	physx::PxQuat q;
	q.w = cy * cp * cr + sy * sp * sr;
	q.x = cy * cp * sr - sy * sp * cr;
	q.y = sy * cp * sr + cy * sp * cr;
	q.z = sy * cp * cr - cy * sp * sr;
	return q;
}

RigidBody::RigidBody(Actor& owner, float mass, eRigidBodyType rb_type) : owner(owner)
{
	// Get PX
	auto& px = Physics::Get();

	this->mass = mass;
	current_type = rb_type;

	// Check if collider exists!
	auto collider = owner.GetComponent<Collider>();
	if (!collider)
	{
		throw std::exception("collider not found!");
	}

	// Select which geometry our collider has
	if (collider->GetGeometryType() == eGeometryType::BOX)
	{
		if (rb_type == eRigidBodyType::DYNAMIC)
		{
			body_dynamic = px.GetPxPhysics()->createRigidDynamic(physx::PxTransform(owner.transform->location.x, owner.transform->location.y, owner.transform->location.z));
			body_dynamic->setMass(mass);
			body_dynamic->attachShape(*collider->GetShape());
			current_body = reinterpret_cast<physx::PxRigidBody*>(body_dynamic);
		}
		else
		{
			body_static = px.GetPxPhysics()->createRigidStatic(physx::PxTransform(owner.transform->location.x, owner.transform->location.y, owner.transform->location.z));
			body_static->attachShape(*collider->GetShape());
			current_body = reinterpret_cast<physx::PxRigidBody*>(body_static);
		}

		if (!current_body)
		{
			throw std::exception("unable to create body_dynamic");
		}

		px.GetPxScene()->addActor(*current_body);

		// Compute geometry tensors space and mass inertia and update them
		physx::PxBoxGeometry box_g;
		collider->GetShape()->getBoxGeometry(box_g);

		// calculate density of the shape
		volume = (box_g.halfExtents.x * box_g.halfExtents.y * box_g.halfExtents.z);
		density = (mass / volume);
	}
	else
	{
		if (rb_type == eRigidBodyType::DYNAMIC)
		{
			body_dynamic = px.GetPxPhysics()->createRigidDynamic(physx::PxTransform(owner.transform->location.x, owner.transform->location.y, owner.transform->location.z));
			body_dynamic->setMass(mass);
			body_dynamic->attachShape(*collider->GetShape());
			current_body = reinterpret_cast<physx::PxRigidBody*>(body_dynamic);
		}
		else
		{
			body_static = px.GetPxPhysics()->createRigidStatic(physx::PxTransform(owner.transform->location.x, owner.transform->location.y, owner.transform->location.z));
			body_static->attachShape(*collider->GetShape());
			current_body = reinterpret_cast<physx::PxRigidBody*>(body_static);
		}

		if (!current_body)
		{
			throw std::exception("unable to create body_dynamic");
		}

		px.GetPxScene()->addActor(*current_body);

		// Compute geometry tensors space and mass inertia and update them
		// Same as the box but we need to extrapolate the density by the radius
		// which is given by square root of xyz components scale of the transform

		// get geometry
		physx::PxSphereGeometry sphere_g;
		collider->GetShape()->getSphereGeometry(sphere_g);

		// calculate density of the shape
		volume = (4 * 3.14f * pow(sphere_g.radius, 3)) / 3;
		density = (current_body->getMass() / volume);
	}
}

void RigidBody::AddForce(const DirectX::SimpleMath::Vector3 force, eForceMode force_mode)
{
	body_dynamic->addForce(physx::PxVec3(force.x, force.y, force.z), static_cast<physx::PxForceMode::Enum>(force_mode));
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
	current_body->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, disable_gravity);
}

void RigidBody::SetRigidBodyCCD(bool use_ccd)
{
	body_dynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, use_ccd);
}

void RigidBody::SetRotation(float x, float y, float z)
{
	auto new_rot = EulerToQuat(x, y, z);

	body_dynamic->setGlobalPose(physx::PxTransform(body_dynamic->getGlobalPose().p, new_rot));
}

float RigidBody::GetDensity() const
{
	return density;
}

void RigidBody::Tick(float delta_time)
{
	// Update inertia and mass tensors space
	if (current_type != eRigidBodyType::STATIC)
		physx::PxRigidBodyExt::updateMassAndInertia(*current_body, density);

	owner.transform->location.x = current_body->getGlobalPose().p.x;
	owner.transform->location.y = current_body->getGlobalPose().p.y;
	owner.transform->location.z = current_body->getGlobalPose().p.z;

	owner.transform->rotation.x = current_body->getGlobalPose().q.x;
	owner.transform->rotation.y = current_body->getGlobalPose().q.y;
	owner.transform->rotation.z = current_body->getGlobalPose().q.z;
	owner.transform->rotation.w = current_body->getGlobalPose().q.w;
}
