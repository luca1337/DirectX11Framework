#pragma once

#include <vector>
#include <memory>
#include <Keyboard.h>

#include "ISystem.h"

class DX11FWEngine
{
public:
	static DX11FWEngine& Get();

	void Initialize(const std::string& window_title, unsigned int width, unsigned int height, float aspect_ratio);

	void Run();

private:

	void AddSystem(ISystem* system);

	void SortSystems();

	std::vector<ISystem*> systems;

	std::unique_ptr<DirectX::Keyboard> keyboard;
	std::shared_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboard_tracker;

	DX11FWEngine();

};
