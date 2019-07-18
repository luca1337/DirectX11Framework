#include "DX11FWEngine.h"

#include "Engine.h"
#include "GraphicsSystem.h"
#include "UpdateSystem.h"
#include "PhysicsSystem.h"
#include "ISystem.h"
#include "World.h"
#include "Camera.h"

#include <Windows.h>

DX11FWEngine::DX11FWEngine()
{
}

DX11FWEngine& DX11FWEngine::Get()
{
	static DX11FWEngine* dx11fw_engine = nullptr;

	if (!dx11fw_engine)
		dx11fw_engine = new DX11FWEngine();

	return *dx11fw_engine;
}

void DX11FWEngine::Initialize(const std::string& window_title, unsigned int width, unsigned int height, float aspect_ratio)
{
	// Init engine
	Engine& engine = Engine::Singleton();

	// Init now all systems such as graphics, physics, update etc..
	auto gs = GraphicSystem::Get();
	auto ps = PhysicsSystem::Get();
	auto us = std::make_shared<UpdateSystem>();

	gs->Init(window_title, width, height, aspect_ratio);
	ps->Init();

	// put all them together
	AddSystem(gs);
	AddSystem(ps);
	AddSystem(us);

	// Init the world that will contains all actors, components
	World& world = World::Get();

	// Init keyboard events
	keyboard = std::make_unique<DirectX::Keyboard>();
	keyboard_tracker = std::make_shared<DirectX::Keyboard::KeyboardStateTracker>();
}

void DX11FWEngine::Run()
{
	// Sort systems before we start running the engine
	SortSystems();

	// TODO: replace while(1) with game_engine.isRunning()
	while (1)
	{
		// Update keyboard events
		keyboard_tracker->Update(keyboard->GetState());

		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Clear screen
		GraphicSystem::Get()->Clear({0.0f, 0.0f, 1.0f, 0.0f});

		// Update camera
		GraphicSystem::Get()->GetMainCamera()->Update(keyboard->GetState());

		GraphicSystem::Get()->delta_time = GraphicSystem::Get()->CalculateDeltaTime();
		// Update all systems such as physics, graphics, update of actors etc..
		for (auto system: systems)
		{
			system->Update(GraphicSystem::Get()->delta_time);
		}
	}
}

void DX11FWEngine::AddSystem(std::shared_ptr<ISystem> system)
{
	systems.push_back(system);
}

void DX11FWEngine::SortSystems()
{
	for (int i = 0; i < systems.size(); i++)
	{
		for (int j = i + 1; j < systems.size(); j++)
		{
			if (systems[i]->update_offset > systems[j]->update_offset)
			{
				auto temp = systems[j];
				systems[j] = systems[i];
				systems[i] = temp;
			}
		}
	}

	for (int i = 0; i < systems.size(); i++)
	{
		std::cout << "sorted: " << systems[i]->update_offset << std::endl;
	}
}
