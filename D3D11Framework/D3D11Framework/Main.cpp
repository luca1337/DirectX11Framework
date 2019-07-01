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

#include "BoxCollider.h"
#include "SphereCollider.h"

#include "Cube.h"
#include "Sphere.h"
#include "Enemy.h"

int main(int argc, char** argv)
{
	// Init engine
	Engine& engine = Engine::Singleton();

	// init graphics pipeline
	Graphics& graphics = Graphics::Singleton();
	graphics.Initialize("D3DFramework", 1024, 720, 1024 / 720);

	// init physics pipeline
	d3d_engine::Physix& physics = d3d_engine::Physix::Get();
	physics.InitPhysix();

	// Setup some light
	Light directional_light = {};
	directional_light.SetLightType(eLightType::DIRECTIONAL_LIGHT);
	directional_light.SetDirection({0.0f, -3.0f, 0.0f});
	directional_light.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	directional_light.SetIntensity(0.8f);
	directional_light.SetActive(true);

	Light point_light00 = {};
	point_light00.SetLightType(eLightType::POINT_LIGHT);
	point_light00.SetPosition({0.0f, 10.0f, 0.0f});
	point_light00.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light00.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	point_light00.SetRange(2.0f);
	point_light00.SetIntensity(2.0f);
	point_light00.SetActive(true);

	Light point_light01 = {};
	point_light01.SetLightType(eLightType::POINT_LIGHT);
	point_light01.SetPosition({ -100.0f, 10.0f, 100.0f });
	point_light01.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light01.SetColor({ 0.0f, 1.0f, 1.0f, 1.0f });
	point_light01.SetRange(2.0f);
	point_light01.SetIntensity(2.0f);
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

	TextureManager::AddTexture("Assets/Textures/robot_albedo.png", "robot_a");
	TextureManager::AddTexture("Assets/Textures/robot_normal.png", "robot_n");

	// Skydome
	std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>("Assets/Models/sphere.txt");

	// create some players and spawn them
	std::shared_ptr<Player> player00 = std::make_shared<Player>("Assets/Models/cube.txt");
	player00->transform->location = { 0.0f, -10.0f, 0.0f };
	player00->transform->rotation = { 0.0f, 0.0f, 0.0f };
	player00->transform->scale = { 300.0f, 5.0f, 300.0f };

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

	auto plane_collider = std::make_shared<BoxCollider>(*player00);
	player00->AddComponent<BoxCollider>(plane_collider);

	// RigidBody component
	auto rigid_body = std::make_shared<RigidBody>(*player00, 10.0f, eRigidBodyType::STATIC);
	rigid_body->SetUseGravity(true);
	player00->AddComponent<RigidBody>(rigid_body);

	// spawn first actor
	world.SpawnActor(player00);

	//////////////////// end plane ///////////////////////////////

	// CUBE PRIMITIVE CREATION
	auto cube = std::make_shared<Cube>(SimpleMath::Vector3(5.0f, 5.0f, 5.0f));
	cube->transform->location.y = 30;

	// RigidBody component
	auto cube_rb = std::make_shared<RigidBody>(*cube, 1.0f, eRigidBodyType::DYNAMIC);
	cube_rb->SetRotation(90, 3, 0);
	cube->AddComponent<RigidBody>(cube_rb);

	world.SpawnActor(cube);

	// SPHERE PRIMITIVE CREATION
	auto sphere = std::make_shared<Sphere>();
	sphere->transform->location = { -10.0f, 20.0f, 0.0f };
	sphere->transform->scale = { 5.0f, 5.0f, 5.0f };

	// RigidBody component
	auto sphere_rb = std::make_shared<RigidBody>(*sphere, 1.0f, eRigidBodyType::DYNAMIC);
	sphere->AddComponent<RigidBody>(sphere_rb);

	world.SpawnActor(sphere);

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
			sphere_rb->AddForce({ 100.0f, 0.0f, 0.0f }, physx::PxForceMode::eFORCE);
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