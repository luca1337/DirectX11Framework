#include "Graphics.h"

#include "Engine.h"
#include "Window.h"
#include "Texture.h"
#include "RenderTarget.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Camera.h"

#include "winrt/Windows.ApplicationModel.Core.h"
#include "winrt/Windows.UI.Core.h"
#include "winrt/Windows.UI.ViewManagement.h"

#include "ShaderManager.h"
#include "ShaderLayoutDesc.h"

#include "Bytecode.h"
#include "GPUConstBuffer.h"
#include "Light.h"

#include "World.h"
#include "Physix.h"

DWORD Graphics::previous_time = 0;
float Graphics::max_time_steps = 0;

Graphics::Graphics()
{
	lights = std::vector<Light>();

	lights_buffer = std::make_unique<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<UINT>(sizeof(Light)) * MAX_LIGHTS);
	lights_properties_buffer = std::make_unique<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<UINT>(sizeof(LightProperties)));

	StartCounter();
}

void Graphics::StartCounter()
{
	previous_time = timeGetTime();
	static const float target_frame_rate = 30.0f;
	max_time_steps = 1.0f / target_frame_rate;
}

float Graphics::CalculateDeltaTime()
{
	DWORD currentTime = timeGetTime();
	float deltaTime = (currentTime - previous_time) / 1000.0f;
	previous_time = currentTime;

	// Cap the delta time to the max time step (useful if your 
	// debugging and you don't want the deltaTime value to explode.
	deltaTime = std::min<float>(deltaTime, max_time_steps);

	return deltaTime;
}

float Graphics::UpdateTime()
{
	float deltaTime;
	static __int64 gTime, gLastTime;
	__int64 freq;

	QueryPerformanceCounter((LARGE_INTEGER *)&gTime);   // Get current count
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);  // Get processor freq
	deltaTime = (float)(gTime - gLastTime) / (float)freq;
	gLastTime = gTime;

	return deltaTime;
}

Graphics& Graphics::Singleton()
{
	static Graphics* graphics = nullptr;

	if (!graphics)
	{
		graphics = new Graphics();
	}

	return *graphics;
}

void Graphics::Initialize(std::string title, unsigned width, unsigned height, float aspect_ratio)
{
	window = std::make_shared<Window>(Engine::Singleton().GetDxDevice(), width, height, title);
	swap_chain = std::make_shared<Texture>(window);
	render_target = std::make_shared<RenderTarget>(swap_chain);

	// add our skydome shader
	ShaderManager::CreateAndAddVertexShaderResource(ShaderLayoutDesc::Vertex, "skydome_vertex", skymap_vs, sizeof(skymap_vs), ShaderLayoutDesc::v_layout_size);
	ShaderManager::CreateAndAddPixelShaderResource("skydome_pixel", skymap_ps, sizeof(skymap_ps));

	// add our basics vertex and pixel shaders
	ShaderManager::CreateAndAddVertexShaderResource(ShaderLayoutDesc::VertexNormalUvTangentBitangent, "basic_vertex", vs001, sizeof(vs001), ShaderLayoutDesc::vnutb_layout_size);
	ShaderManager::CreateAndAddPixelShaderResource("basic_pixel", ps001, sizeof(ps001));

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();

	// DEPTH STENCIL
	depth_texture = std::make_shared<Texture>(1280, 1024, DXGI_FORMAT_D24_UNORM_S8_UINT);
	depth_target = std::make_shared<DepthTarget>(depth_texture);
	render_target->Bind(depth_target);

	// MAIN CAMERA
	main_camera = std::make_shared<Camera>();
	main_camera->SetCameraProjection(45.0f, aspect_ratio, 0.01f, 10000.0f);
	main_camera->SetPosition(0.0f, 0.0f, -10.0f);
	main_camera->SetRotation(0.0f, 0.0f, 0.0f);
}

void Graphics::AddLight(std::initializer_list<Light> light)
{
	for (auto It = light.begin(); It != light.end(); ++It)
	{
		lights.push_back(*It);
	}
}

std::shared_ptr<Camera> Graphics::GetMainCamera() const
{
	return main_camera;
}

void Graphics::Clear()
{
	render_target->Clear({0.4f, 0.4f, 0.4f, 0.4f});
	depth_target->Clear();

	delta_time = CalculateDeltaTime();
}

void Graphics::Present()
{
	World::Get().Tick(delta_time);

	d3d_engine::Physix::Get().UpdatePhysx(delta_time);

	window->Present();
}