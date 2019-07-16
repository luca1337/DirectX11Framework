#pragma once

#include <PxPhysicsAPI.h>
#include <memory>

class DX11FWAllocator;
class DX11FWDispatcher;
class DX11FWErrorCallback;
class DX11FWSimulationEvent;

class PhysicsMaterial;

class Physics
{
public:
	// Singleton
	static Physics& Get();

	physx::PxScene* GetPxScene();
	physx::PxPhysics* GetPxPhysics();

	void InitPhysix();
	void UpdatePhysx(float delta_time);

	std::unique_ptr<PhysicsMaterial> default_physics_material;

	~Physics();

private:
	physx::PxScene* scene;
	physx::PxPhysics* physics;

	// Allocators and Events
	std::unique_ptr<DX11FWAllocator> dx11_allocator;
	std::unique_ptr<DX11FWDispatcher> dx11_dispatcher;
	std::unique_ptr<DX11FWErrorCallback> dx11_error_callback;
	std::unique_ptr<DX11FWSimulationEvent> dx11_simulation_event;
};