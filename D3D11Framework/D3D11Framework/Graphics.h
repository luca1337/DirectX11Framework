#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Light.h"
#include <Windows.h>

#define MAX_LIGHTS 10

class RenderTarget;
class Texture;
class Window;
class Camera;
class VertexShader;
class PixelShader;
class DepthTarget;
class GPUConstBuffer;
class Mesh;

class Graphics final
{
public:
	static Graphics& Singleton();

	void Initialize(std::string title, unsigned width, unsigned height, float aspect_ratio);

	void AddLight(std::initializer_list<Light> lights);

	void Clear();

	void Present();

	std::shared_ptr<Camera> GetMainCamera() const;

	// BASIC SHADERS
	std::shared_ptr<VertexShader> vertex_shader;
	std::shared_ptr<PixelShader> pixel_shader;

	// SKYMAP SHADERS
	std::shared_ptr<VertexShader> skymap_vertex_shader;
	std::shared_ptr<PixelShader> skymap_pixel_shader;

	// COLLIDER SHADERS
	std::shared_ptr<VertexShader> collider_vertex_shader;
	std::shared_ptr<PixelShader> collider_pixel_shader;

	std::unique_ptr<GPUConstBuffer> lights_buffer;

	std::unique_ptr<GPUConstBuffer> lights_properties_buffer;

	std::vector<Light> lights;

	float delta_time;

	void StartCounter();
private:
	Graphics();

	std::shared_ptr<Window> window;
	std::shared_ptr<Texture> swap_chain;
	std::shared_ptr<RenderTarget> render_target;

	std::shared_ptr<Texture> depth_texture;
	std::shared_ptr<DepthTarget> depth_target;

	std::shared_ptr<Camera> main_camera;

	static DWORD previous_time;
	static float max_time_steps;

	float CalculateDeltaTime();

	float UpdateTime();
};