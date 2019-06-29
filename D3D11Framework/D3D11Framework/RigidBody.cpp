#include "RigidBody.h"
#include "Physix.h"
#include "Actor.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

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

static physx::PxQuat EulerToQuat(double yaw, double pitch, double roll) // yaw (Z), pitch (Y), roll (X)
{
	// Abbreviations for the various angular functions
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

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
	auto px = d3d_engine::Physix::Get();

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

	// Convert from quaternion to euler angles
	QuatToEuler(current_body->getGlobalPose().q, this->roll, this->pitch, this->yaw);

	owner.transform->rotation.x = this->roll;
	owner.transform->rotation.y = this->pitch;
	owner.transform->rotation.z = this->yaw;
}
