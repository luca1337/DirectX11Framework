#include "Physix.h"

physx::PxPhysics* d3d_engine::Physix::GetPxPhysics()
{
	return physics;
}

physx::PxMaterial * d3d_engine::Physix::GetPxMaterial()
{
	return material;
}

std::shared_ptr<physx::PxSceneDesc> d3d_engine::Physix::GetPxSceneDesc()
{
	return scene_desc;
}

void d3d_engine::Physix::InitPhysix()
{
	CustomAllocator* custom_allocator = new CustomAllocator();
	CustomErrorCallback* custom_error_callback = new CustomErrorCallback();

	physx::PxFoundation* foundation = PxCreateFoundation(PX_PHYSICS_VERSION, *custom_allocator, *custom_error_callback);
	if (!foundation)
	{
		throw std::exception("unable to create foundation");
	}

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale());
	if (!physics)
	{
		throw std::exception("unable to create physics engine");
	}

	CustomDispatcher* dispatcher = new CustomDispatcher();
	CustomSimulationEvent* evt = new CustomSimulationEvent();

	scene_desc = std::make_shared<physx::PxSceneDesc>(physics->getTolerancesScale());
	scene_desc->gravity = physx::PxVec3(0, -9.81, 0);
	scene_desc->cpuDispatcher = dispatcher;
	scene_desc->simulationEventCallback = evt;
	scene_desc->filterShader = FooShader;
	scene_desc->flags |= physx::PxSceneFlag::eENABLE_CCD;

	scene = physics->createScene(*scene_desc);
	if (!scene)
	{
		throw std::exception("unable to create scene");
	}
}

void d3d_engine::Physix::UpdatePhysx(float delta_time)
{
	scene->simulate(delta_time);
	scene->fetchResults(true);
}

d3d_engine::Physix::~Physix()
{
}

d3d_engine::Physix & d3d_engine::Physix::Get()
{
	static Physix* physix = nullptr;

	if (!physix)
	{
		physix = new Physix();
	}

	return *physix;
}

physx::PxScene * d3d_engine::Physix::GetPxScene()
{
	return scene;
}
