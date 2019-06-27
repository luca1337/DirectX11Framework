#include "ShaderObject.h"
#include "Mesh.h"
#include "Light.h"
#include "Transform.h"
#include "GPUConstBuffer.h"
#include "Camera.h"
#include "ShaderObject.h"
#include "Texture.h"
#include <time.h>
#include "SkyDome.h"
#include "ShaderManager.h"
#include "Material.h"

#include "Engine.h"
#include "Graphics.h"
#include "Utils.h"

#include <Keyboard.h>

#include "DxMenu.h"

#include "Player.h"
#include "World.h"

#include "RotatorComponent.h"

#include "RigidBody.h"
#include "Physix.h"

#include "TextureManager.h"

int main(int argc, char** argv)
{
	// Init engine
	Engine& engine = Engine::Singleton();

	// init graphics pipeline
	Graphics& graphics = Graphics::Singleton();
	graphics.Initialize("D3DFramework", 1280, 1024, 1280 / 1024);

	// init physics pipeline
	d3d_engine::Physix& physics = d3d_engine::Physix::Get();
	physics.InitPhysix();

	// Setup some light
	Light directional_light = {};
	directional_light.SetLightType(eLightType::DIRECTIONAL_LIGHT);
	directional_light.SetDirection({0.0f, -3.0f, 0.0f});
	directional_light.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	directional_light.SetIntensity(0.5f);
	directional_light.SetActive(true);

	Light point_light00 = {};
	point_light00.SetLightType(eLightType::POINT_LIGHT);
	point_light00.SetPosition({0.0f, 10.0f, 0.0f});
	point_light00.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light00.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	point_light00.SetRange(2.0f);
	point_light00.SetIntensity(3.0f);
	point_light00.SetActive(true);

	Light point_light01 = {};
	point_light01.SetLightType(eLightType::POINT_LIGHT);
	point_light01.SetPosition({ -100.0f, 10.0f, 100.0f });
	point_light01.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light01.SetColor({ 0.0f, 1.0f, 1.0f, 1.0f });
	point_light01.SetRange(3.0f);
	point_light01.SetIntensity(4.0f);
	point_light01.SetActive(true);

	graphics.AddLight({directional_light, point_light00, point_light01 });

	// Mesh creation
	std::shared_ptr<Mesh> mesh01 = std::make_shared<Mesh>("Assets/Models/cube.txt");
	mesh01->Scale(300.0f, 0.0f, 300.0f);
	mesh01->SetPosition({ 0.0f, -10.0f, 0.0f });

	engine.RegisterComponent<Transform>();
	engine.RegisterComponent<RigidBody>();
	engine.RegisterComponent<MeshRenderer>();
	engine.RegisterComponent<RotatorComponent>();

	// Create the world
	World& world = World::Get();

	// -- CREATE AND ADD IN MEMORY SOME MANAGED TEXTURES -- //
	TextureManager::AddTexture("Assets/Textures/Abstract_albedo.jpg", "abstract_a");
	TextureManager::AddTexture("Assets/Textures/Abstract_normal.jpg", "abstract_n");

	TextureManager::AddTexture("Assets/Textures/organic_albedo.jpg", "organic_a");
	TextureManager::AddTexture("Assets/Textures/organic_normal.jpg", "organic_n");

	TextureManager::AddTexture("Assets/Textures/wood_albedo.jpg", "wood_a");
	TextureManager::AddTexture("Assets/Textures/wood_normal.jpg", "wood_n");

	// Skydome
	std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>("Assets/Models/sphere.txt");

	// create some players and spawn them
	std::shared_ptr<Player> player00 = std::make_shared<Player>("Assets/Models/cube.txt");
	player00->transform->location = { 0.0f, -10.0f, 0.0f };
	player00->transform->rotation = { 0.0f, 0.0f, 0.0f };
	player00->transform->scale = { 300.0f, 1.0f, 300.0f };

	// create a new material
	auto wood_material = std::make_shared<Material>();
	wood_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	wood_material->SetAmbient({ 0.3f, 0.0f, 0.0f, 1.0f });
	wood_material->SetDiffuse({ 0.3f, 0.3f, 0.3f, 1.0f });
	wood_material->SetSpecular({ 0.7f, 0.5f, 0.7f, 1.0f });
	wood_material->SetSpecularExponent(72.0f);
	wood_material->SetUseAlbedo(true);
	wood_material->SetUseNormalMap(true);

	auto renderer00 = player00->GetComponent<MeshRenderer>();
	renderer00->SetAlbedo("wood_a");
	renderer00->SetNormal("wood_n");
	renderer00->AssignMaterial(wood_material);

	// RigidBody component
	std::shared_ptr<RigidBody> rigid_body = std::make_shared<RigidBody>(*player00.get(), 1.0f, 1.0f, 0.1f, 1.0f);
	auto geometry = rigid_body->CreateRigidBodyBoxGeometry();
	auto shape = rigid_body->CreateShapeAndAttachGeometry(geometry);
	rigid_body->CreateStaticBodyAndAttachShape(shape);
	player00->AddComponent<RigidBody>(rigid_body);

	// spawn first actor
	world.SpawnActor(player00);

	// create another player
	std::shared_ptr<Player> player01 = std::make_shared<Player>("Assets/Models/cube.txt");
	player01->transform->location = { -10.0f, 40.0f, 60.0f };
	player01->transform->rotation = { 0.0f, 0.0f, 0.0f };
	player01->transform->scale = { 10.0f, 15.0f, 7.0f };

	auto renderer01 = player01->GetComponent<MeshRenderer>();
	renderer01->SetAlbedo("abstract_a");
	renderer01->SetNormal("abstract_n");

	// RigidBody component
	std::shared_ptr<RigidBody> rigid_body01 = std::make_shared<RigidBody>(*player01.get(), 1.0f, 4.0f, 0.0f, 0.0f);
	auto geometry01 = rigid_body01->CreateRigidBodyBoxGeometry();
	auto shape01 = rigid_body01->CreateShapeAndAttachGeometry(geometry01);
	rigid_body01->CreateDynamicBodyAndAttachShape(shape01);
	player01->AddComponent<RigidBody>(rigid_body01);

	// spawn second actor
	world.SpawnActor(player01);

	// create a sphere with some component and some material :P
	std::shared_ptr<Player> player02 = std::make_shared<Player>("Assets/Models/sphere.txt");
	player02->transform->location = { -15.0f, 10.0f, 30.0f };
	player02->transform->rotation = { 0.0f, 0.0f, 0.0f };
	player02->transform->scale = { 5.0f, 5.0f, 5.0f };

	// create a new material
	auto plastic_material = std::make_shared<Material>();
	plastic_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	plastic_material->SetAmbient({ 0.3f, 0.0f, 0.0f, 1.0f });
	plastic_material->SetDiffuse({ 0.3f, 0.01f, 0.23f, 1.0f });
	plastic_material->SetSpecular({ 0.3f, 0.2f, 0.5f, 1.0f });
	plastic_material->SetSpecularExponent(72.0f);

	// set the texture with normal map
	auto renderer02 = player02->GetComponent<MeshRenderer>();
	renderer02->AssignMaterial(plastic_material);

	// Add RigidBody
	std::shared_ptr<RigidBody> rigid_body02 = std::make_shared<RigidBody>(*player02.get(), 1.0f, 1.0f, 0.1f, 0.0f);
	auto geometry02 = rigid_body02->CreateRigidBodySphereGeometry(5.0f);
	auto shape02 = rigid_body02->CreateShapeAndAttachGeometry(geometry02);
	rigid_body02->CreateDynamicBodyAndAttachShape(shape02);
	rigid_body02->SetUseGravity(false);
	player02->AddComponent<RigidBody>(rigid_body02);

	world.SpawnActor(player02);

	// create a wall of cubes/spheres to shoot
	int max = 15;
	auto shapes = std::vector< std::shared_ptr<Player>>(max);

	float start_x = -30.0f;
	float start_y = 30.0f;
	float start_z = 100.0f;

	float move_offset = 10.0f;

	for (int i = 0; i < max; i++)
	{
		if (i % 5 == 0)
		{
			start_y -= move_offset;
			start_x = -40.0f;
		}

		shapes[i] = std::make_shared<Player>("Assets/Models/sphere.txt");
		shapes[i]->transform->location = { start_x, start_y, start_z };
		shapes[i]->transform->rotation = {};
		shapes[i]->transform->scale = { 5.0f, 5.0f, 5.0f };

		shapes[i]->GetComponent<MeshRenderer>()->AssignMaterial(plastic_material);
		
		auto rigid_body03 = std::make_shared<RigidBody>(*shapes[i].get(), 1.0f, 1.0f, 0.1f, 0.0f);
		auto geometry03 = rigid_body03->CreateRigidBodySphereGeometry(5.0f);
		auto shape03 = rigid_body03->CreateShapeAndAttachGeometry(geometry03);
		rigid_body03->CreateDynamicBodyAndAttachShape(shape03);
		rigid_body03->SetUseGravity(false);
		shapes[i]->AddComponent(rigid_body03);

		start_x += move_offset;

		world.SpawnActor(shapes[i]);
	}
	
	// Keyboard tracking
	std::unique_ptr<DirectX::Keyboard> keyboard = std::make_unique<DirectX::Keyboard>();
	DirectX::Keyboard::KeyboardStateTracker tracker;

	for (;;)
	{
		// Keyboard events
		auto state = keyboard->GetState();
		tracker.Update(state);

		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		graphics.Clear();

		skydome->Render();

		#pragma region INPUT

		if (state.IsKeyDown(DirectX::Keyboard::Keys::H))
		{
			rigid_body02->AddForce({ 0.0f, 0.0f, 100.0f }, physx::PxForceMode::eFORCE);
		}

		if (state.IsKeyDown(DirectX::Keyboard::Keys::W))
		{
			graphics.GetMainCamera()->Translate(graphics.GetMainCamera()->GetForwardVector() * 30.0f * graphics.delta_time);
		}

		if (state.S)
		{
			graphics.GetMainCamera()->Translate(graphics.GetMainCamera()->GetBackwardVector() * 30.0f * graphics.delta_time);
		}

		if (state.A)
		{
			graphics.GetMainCamera()->Translate(graphics.GetMainCamera()->GetLeftVector() * 30.0f * graphics.delta_time);
		}

		if (state.D)
		{
			graphics.GetMainCamera()->Translate(graphics.GetMainCamera()->GetRightVector() * 30.0f * graphics.delta_time);
		}

		if (state.Right)
		{
			graphics.GetMainCamera()->Rotate(0.0f, 0.0f, 1.0f * graphics.delta_time);
		}

		if (state.Left)
		{
			graphics.GetMainCamera()->Rotate(0.0f, 0.0f, -1.0f * graphics.delta_time);
		}

		if (state.Up)
		{
			graphics.GetMainCamera()->Rotate(0.0f, 1.0f * graphics.delta_time, 0.0f);
		}

		if (state.Down)
		{
			graphics.GetMainCamera()->Rotate(0.0f, -1.0f * graphics.delta_time, 0.0f);
		}

		if (state.E)
		{
			graphics.GetMainCamera()->Translate(graphics.GetMainCamera()->GetUpVector() * 30.0f * graphics.delta_time);
		}

		if (state.Q)
		{
			graphics.GetMainCamera()->Translate(graphics.GetMainCamera()->GetDownVector() * 30.0f * graphics.delta_time);
		}
#pragma endregion

		graphics.Present();
	}

	return 0;
}