#include "Physics.h"
#include "PhysicsMaterial.h"
#include "DX11FWAllocator.h"
#include "DX11FWErrorCallback.h"
#include "DX11FWDispatcher.h"
#include "DX11FWSimulationEvent.h"
#include "DX11FWShaderFilter.h"

Physics& Physics::Get()
{
	static Physics* physix = nullptr;

	if (!physix)
	{
		physix = new Physics();
	}

	return *physix;
}

void Physics::InitPhysix()
{
	dx11_allocator = std::make_unique<DX11FWAllocator>();
	dx11_error_callback = std::make_unique<DX11FWErrorCallback>();

	try
	{
		physx::PxFoundation* foundation = PxCreateFoundation(PX_PHYSICS_VERSION, *dx11_allocator, *dx11_error_callback);
		physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale());
	}
	catch (...)
	{
		std::cerr << "exception occurred while trying to create Physx foundation, aborting.." << std::endl;
	}

	dx11_dispatcher = std::make_unique<DX11FWDispatcher>();
	dx11_simulation_event = std::make_unique<DX11FWSimulationEvent>();

	auto scene_desc = physx::PxSceneDesc(physics->getTolerancesScale());
	scene_desc.gravity = physx::PxVec3(0, -9.81f, 0);
	scene_desc.cpuDispatcher = dx11_dispatcher.get();
	scene_desc.simulationEventCallback = dx11_simulation_event.get();
	scene_desc.filterShader = &DX11FWShaderFilter::FooShader;
	//scene_desc->flags |= physx::PxSceneFlag::eENABLE_CCD;

	try
	{
		scene = physics->createScene(scene_desc);
	}
	catch (...)
	{
		std::cerr << "exception occurred while creating Physx scene, aborting.." << std::endl;
	}

	default_physics_material = std::make_unique<PhysicsMaterial>();
}

physx::PxPhysics* Physics::GetPxPhysics()
{
	return physics;
}

void Physics::UpdatePhysx(float delta_time)
{
	scene->simulate(delta_time);
	scene->fetchResults(true);
}

physx::PxScene * Physics::GetPxScene()
{
	return scene;
}

Physics::~Physics()
{
	scene->release();
	physics->release();
}
