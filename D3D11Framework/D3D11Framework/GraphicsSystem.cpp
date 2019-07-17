#include "GraphicsSystem.h"
#include "Window.h"
#include "Texture.h"
#include "RenderTarget.h"
#include "DepthTarget.h"
#include "Camera.h"
#include "GPUConstBuffer.h"
#include "Light.h"
#include "ShaderManager.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Bytecode.h"
#include "ShaderLayoutDesc.h"
#include "Light.h"
#include <algorithm>

DWORD GraphicSystem::previous_time = 0;
float GraphicSystem::max_time_steps = 0.0f;

GraphicSystem& GraphicSystem::Get()
{
	static GraphicSystem* gs = nullptr;

	if (!gs)
		gs = new GraphicSystem();

	return *gs;
}

void GraphicSystem::Update(float delta_time)
{
	delta_time = CalculateDeltaTime();
	window->Present();
}

void GraphicSystem::Init(const std::string& window_title, unsigned int width, unsigned int height, float aspect_ratio)
{
	// Init the graphics pipeline
	window = std::make_shared<Window>(width, height, window_title);
	swap_chain_texture = std::make_shared<Texture>(window);
	swap_chain_render_target = std::make_shared<RenderTarget>(swap_chain_texture);

	// Depth Stencil
	window_depth_texture = std::make_shared<Texture>(width, height, DXGI_FORMAT_D24_UNORM_S8_UINT);
	window_depth_target = std::make_shared<DepthTarget>(window_depth_texture);
	swap_chain_render_target->Bind(window_depth_target);

	// 3D Camera
	main_camera = std::make_shared<Camera>();
	main_camera->SetCameraProjection(60.0f, aspect_ratio, 0.01f, 1000.0f);
	main_camera->SetPosition(SimpleMath::Vector3(0.0f, 0.0f, -10.0f));
	main_camera->SetRotation(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}

void GraphicSystem::Clear(std::initializer_list<float> colors)
{
	swap_chain_render_target->Clear(colors);
	window_depth_target->Clear();
}

void GraphicSystem::StartCounter()
{
	previous_time = timeGetTime();
	static const float target_frame_rate = 30.0f;
	max_time_steps = 1.0f / target_frame_rate;
}

float GraphicSystem::CalculateDeltaTime()
{
	DWORD currentTime = timeGetTime();
	float deltaTime = (currentTime - previous_time) / 1000.0f;
	previous_time = currentTime;

	// Cap the delta time to the max time step
	deltaTime = std::min<float>(deltaTime, max_time_steps);

	return deltaTime;
}

std::shared_ptr<Camera> GraphicSystem::GetMainCamera() const
{
	return main_camera;
}

void GraphicSystem::AddSceneLight(Light & light)
{
	lights.push_back(light);
}

GraphicSystem::GraphicSystem()
{
	// do not change this!!!
	update_offset = 1;

	lights_buffer = std::make_unique<GPUConstBuffer>(static_cast<UINT>(sizeof(Light)) * max_lights);
	lights_properties_buffer = std::make_unique<GPUConstBuffer>(static_cast<UINT>(sizeof(LightProperties)));

	// Add some shaders
	ShaderManager::CreateAndAddVertexShaderResource(ShaderLayoutDesc::Vertex, "skydome_vertex", skymap_vs, sizeof(skymap_vs), ShaderLayoutDesc::v_layout_size);
	ShaderManager::CreateAndAddPixelShaderResource("skydome_pixel", skymap_ps, sizeof(skymap_ps));

	ShaderManager::CreateAndAddVertexShaderResource(ShaderLayoutDesc::Vertex, "collider_vertex", collider_vertex, sizeof(collider_vertex), ShaderLayoutDesc::v_layout_size);
	ShaderManager::CreateAndAddPixelShaderResource("collider_pixel", collider_pixel, sizeof(collider_pixel));

	ShaderManager::CreateAndAddVertexShaderResource(ShaderLayoutDesc::VertexNormalUv, "sprite_vertex", sprite_vs, sizeof(sprite_vs), ShaderLayoutDesc::vnu_layout_size);
	ShaderManager::CreateAndAddPixelShaderResource("sprite_pixel", sprite_ps, sizeof(sprite_ps));

	ShaderManager::CreateAndAddVertexShaderResource(ShaderLayoutDesc::VertexNormalUvTangentBitangent, "basic_vertex", vs001, sizeof(vs001), ShaderLayoutDesc::vnutb_layout_size);
	ShaderManager::CreateAndAddPixelShaderResource("basic_pixel", ps001, sizeof(ps001));

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();

	// delta time
	StartCounter();
}
