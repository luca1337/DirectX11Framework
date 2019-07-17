#pragma once

#include "ISystem.h"

#include <vector>
#include <string>
#include <memory>
#include <Windows.h>

class Window;
class Texture;
class RenderTarget;
class DepthTarget;
class Camera;
class GPUConstBuffer;
struct Light;

class GraphicSystem : public ISystem
{
public:
	static GraphicSystem& Get();

	virtual void Update(float delta_time) override;

	void Init(const std::string& window_title, unsigned int width, unsigned int height, float aspect_ratio);

	void Clear(std::initializer_list<float> colors);

	void StartCounter();

	float CalculateDeltaTime();

	std::shared_ptr<Camera> GetMainCamera() const;

	void AddSceneLight(Light& light);

	float delta_time;

	const unsigned long max_lights = 10;

	std::unique_ptr<GPUConstBuffer> lights_buffer;
	std::unique_ptr<GPUConstBuffer> lights_properties_buffer;
	std::vector<Light>				lights;

private:
	GraphicSystem();

	std::shared_ptr<Window>			window;
	std::shared_ptr<Texture>		swap_chain_texture;
	std::shared_ptr<RenderTarget>	swap_chain_render_target;
	std::shared_ptr<Texture>		window_depth_texture;
	std::shared_ptr<DepthTarget>	window_depth_target;
	std::shared_ptr<Camera>			main_camera;

	static DWORD previous_time;
	static float max_time_steps;
};