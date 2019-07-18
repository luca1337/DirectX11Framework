#pragma once

#include <vector>
#include <memory>
#include <Keyboard.h>

struct ISystem;

class DX11FWEngine final
{
public:
	static DX11FWEngine& Get();

	void AddSystem(std::shared_ptr<ISystem> system);

	void Initialize(const std::string& window_title, unsigned int width, unsigned int height, float aspect_ratio);

	void Run();

private:

	void SortSystems();

	std::unique_ptr<DirectX::Keyboard> keyboard;
	std::shared_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboard_tracker;

	DX11FWEngine();

	std::vector<std::shared_ptr<ISystem>> systems;
};
