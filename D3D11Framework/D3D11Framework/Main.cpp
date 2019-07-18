#include "Light.h"
#include "TextureManager.h"
#include "GraphicsSystem.h"
#include "Engine.h"
#include "World.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "Material.h"
#include "Sphere.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Player.h"
#include "Actor.h"
#include "SkyDome.h"
#include "DX11FWEngine.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Quad.h"
#include "Core.h"
#include <SimpleMath.h>

using namespace DirectX;

int main(int argc, char** argv)
{
	// Init GameEngine
	DX11FWEngine& dx11fw_engine = DX11FWEngine::Get();
	dx11fw_engine.Initialize("DX11Engine", 1024, 1024, 1);

	// Setup some light
	Light directional_light = {};
	directional_light.SetLightType(eLightType::DIRECTIONAL_LIGHT);
	directional_light.SetDirection({ 0.0f, -3.0f, 0.0f });
	directional_light.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	directional_light.SetIntensity(1.0f);
	directional_light.SetActive(true);

	Light point_light00 = {};
	point_light00.SetLightType(eLightType::POINT_LIGHT);
	point_light00.SetPosition({ -45.0f, 0.0f, -30.0f });
	point_light00.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light00.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	point_light00.SetRange(3.0f);
	point_light00.SetIntensity(2.0f);
	point_light00.SetActive(true);

	Light point_light01 = {};
	point_light01.SetLightType(eLightType::POINT_LIGHT);
	point_light01.SetPosition({ -30.0f, 50.0f, 80.0f });
	point_light01.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light01.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	point_light01.SetRange(3.0f);
	point_light01.SetIntensity(2.0f);
	point_light01.SetActive(true);

	Light point_light02 = {};
	point_light02.SetLightType(eLightType::POINT_LIGHT);
	point_light02.SetPosition({ -30.0f, 50.0f, 120.0f });
	point_light02.SetAttenuation({ 1.0f, 0.08f, 0.0f });
	point_light02.SetColor({ .0f, 1.0f, 1.0f, 1.0f });
	point_light02.SetRange(2.0f);
	point_light02.SetIntensity(2.0f);
	point_light02.SetActive(true);

	GraphicSystem::Get()->AddSceneLight(directional_light);
	GraphicSystem::Get()->AddSceneLight(point_light00);
	GraphicSystem::Get()->AddSceneLight(point_light01);

	Engine::Singleton().RegisterComponent<Transform>();
	Engine::Singleton().RegisterComponent<RigidBody>();
	Engine::Singleton().RegisterComponent<MeshRenderer>();

	// -- CREATE AND ADD IN MEMORY SOME MANAGED TEXTURES -- //
	TextureManager::AddTexture("Assets/Textures/Abstract_albedo.jpg", "abstract_a");
	TextureManager::AddTexture("Assets/Textures/Abstract_normal.jpg", "abstract_n");

	TextureManager::AddTexture("Assets/Textures/organic_albedo.jpg", "organic_a");
	TextureManager::AddTexture("Assets/Textures/organic_normal.jpg", "organic_n");

	TextureManager::AddTexture("Assets/Textures/wood_albedo.jpg", "wood_a");
	TextureManager::AddTexture("Assets/Textures/wood_normal.jpg", "wood_n");

	TextureManager::AddTexture("Assets/Textures/wood_smooth_albedo.jpg", "wood_s_a");
	TextureManager::AddTexture("Assets/Textures/wood_smooth_normal.jpg", "wood_s_n");

	TextureManager::AddTexture("Assets/Textures/metal_raw_albedo.jpg", "metal_raw_a");
	TextureManager::AddTexture("Assets/Textures/metal_raw_normal.jpg", "metal_raw_n");

	TextureManager::AddTexture("Assets/Textures/marble_albedo.jpg", "marble_a");
	TextureManager::AddTexture("Assets/Textures/marble_normal.jpg", "marble_n");

	TextureManager::AddTexture("Assets/Textures/grid.png", "grid");
	TextureManager::AddTexture("Assets/Textures/BoltPW.png", "bolt");

	// Skydome
	std::shared_ptr<Skydome> skydome = std::make_shared<Skydome>("Assets/Models/sphere.txt");

	// create some players and spawn them
	std::shared_ptr<Player> player00 = std::make_shared<Player>("Assets/Models/cube.txt");
	player00->transform->location = { 0.0f, -10.0f, 0.0f };
	player00->transform->rotation = { 0.0f, -0.5f, 0.0f };
	player00->transform->scale = { 600.0f, 5.0f, 600.0f };

	// create a new material
	auto marble_material = std::make_shared<Material>();
	marble_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	marble_material->SetAmbient({ 0.25f, 0.25f, 0.25f, 1.0f });
	marble_material->SetDiffuse({ 0.4f, 0.4f, 0.4f, 1.0f });
	marble_material->SetSpecular({ 0.77f, 0.77f, 0.77f, 1.0f });
	marble_material->SetSpecularExponent(76.8f);
	marble_material->SetUseAlbedo(true);
	marble_material->SetUseNormalMap(false);

	auto renderer00 = player00->GetComponent<MeshRenderer>();
	renderer00->SetAlbedo("metal_raw_a");
	renderer00->SetNormal("metal_raw_n");
	renderer00->AssignMaterial(marble_material);

	auto plane_collider = std::make_shared<BoxCollider>(*player00);
	player00->AddComponent<BoxCollider>(plane_collider);

	// RigidBody component
	auto rigid_body = std::make_shared<RigidBody>(*player00, 1.0f, eRigidBodyType::STATIC);
	rigid_body->SetUseGravity(true);
	player00->AddComponent<RigidBody>(rigid_body);

	World& world = World::Get();

	// spawn first actor
	world.SpawnActor(player00);

	//////////////////// end plane ///////////////////////////////

	// - Let's create some materials so that we can show up different effects.

	// Dark red plastic
	auto red_plastic_material = std::make_shared<Material>();
	red_plastic_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	red_plastic_material->SetAmbient({ 0.5f, 0.1f, 0.1f, 1.0f });
	red_plastic_material->SetDiffuse({ 0.5f, 0.1f, 0.1f, 1.0f });
	red_plastic_material->SetSpecular({ 0.7f, 0.2f, 0.2f, 1.0f });
	red_plastic_material->SetSpecularExponent(32.0f);
	red_plastic_material->SetUseAlbedo(false);
	red_plastic_material->SetUseNormalMap(false);

	// Cyan plastic
	auto cyan_plastic_material = std::make_shared<Material>();
	cyan_plastic_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	cyan_plastic_material->SetAmbient({ 0.0f, 0.1f, 0.06f, 1.0f });
	cyan_plastic_material->SetDiffuse({ 0.0f, 0.5f, 0.5f, 1.0f });
	cyan_plastic_material->SetSpecular({ 0.5f, 0.5f, 0.5f, 1.0f });
	cyan_plastic_material->SetSpecularExponent(32.0f);
	cyan_plastic_material->SetUseAlbedo(false);
	cyan_plastic_material->SetUseNormalMap(false);

	// Cyan plastic
	auto jade_material = std::make_shared<Material>();
	jade_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	jade_material->SetAmbient({ 0.13f, 0.22f, 0.15f, 1.0f });
	jade_material->SetDiffuse({ 0.54f, 0.89f, 0.63f, 1.0f });
	jade_material->SetSpecular({ 0.31f, 0.31f, 0.31f, 1.0f });
	jade_material->SetSpecularExponent(12.8f);
	jade_material->SetUseAlbedo(false);
	jade_material->SetUseNormalMap(false);

	// Textured
	auto textured_material = std::make_shared<Material>();
	textured_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	textured_material->SetAmbient({ 1.0f, 1.0f, 1.0f, 1.0f });
	textured_material->SetDiffuse({ 1.0f, 1.0f, 1.0f, 1.0f });
	textured_material->SetSpecular({ 0.5f, 0.5f, 0.5f, 1.0f });
	textured_material->SetSpecularExponent(32.0f);
	textured_material->SetUseAlbedo(true);
	textured_material->SetUseNormalMap(true);

	// Textured metal
	auto textured_chrome_material = std::make_shared<Material>();
	textured_chrome_material->SetEmissive({ 0.0f, 0.0f, 0.0f, 1.0f });
	textured_chrome_material->SetAmbient({ 0.25f, 0.25f, 0.25f, 1.0f });
	textured_chrome_material->SetDiffuse({ 0.4f, 0.4f, 0.4f, 1.0f });
	textured_chrome_material->SetSpecular({ 0.77f, 0.77f, 0.77f, 1.0f });
	textured_chrome_material->SetSpecularExponent(76.8f);
	textured_chrome_material->SetUseAlbedo(true);
	textured_chrome_material->SetUseNormalMap(true);

	// Create some shapes and assign materials

	// - Sphere 1 
	auto sphere00 = std::make_shared<Sphere>();
	sphere00->transform->location = SimpleMath::Vector3(0.0f, 0.0f, 15.0f);
	sphere00->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);
	auto render_component00 = sphere00->GetComponent<MeshRenderer>();
	render_component00->AssignMaterial(red_plastic_material);
	world.SpawnActor(sphere00);
	// - End

	// - Sphere 2
	auto sphere01 = std::make_shared<Sphere>();
	sphere01->transform->location = SimpleMath::Vector3(15.0f, 0.0f, 15.0f);
	sphere01->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);
	auto render_component01 = sphere01->GetComponent<MeshRenderer>();
	render_component01->AssignMaterial(cyan_plastic_material);
	world.SpawnActor(sphere01);
	// - End

	// - Sphere 3
	auto sphere02 = std::make_shared<Sphere>();
	sphere02->transform->location = SimpleMath::Vector3(30.0f, 0.0f, 15.0f);
	sphere02->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);
	auto render_component02 = sphere02->GetComponent<MeshRenderer>();
	render_component02->AssignMaterial(jade_material);
	world.SpawnActor(sphere02);
	// - End

	// - TEXTURED SHAPES -

	// - Sphere 4
	auto sphere03 = std::make_shared<Sphere>();
	sphere03->transform->location = SimpleMath::Vector3(-30.0, 0.0f, 15.0f);
	sphere03->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);
	auto render_component03 = sphere03->GetComponent<MeshRenderer>();
	render_component03->SetAlbedo("abstract_a");
	render_component03->SetNormal("abstract_n");
	render_component03->AssignMaterial(textured_material);
	world.SpawnActor(sphere03);
	// - End

	// - Sphere 5
	auto sphere04 = std::make_shared<Sphere>();
	sphere04->transform->location = SimpleMath::Vector3(-45.0, 0.0f, 15.0f);
	sphere04->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);
	auto render_component04 = sphere04->GetComponent<MeshRenderer>();
	render_component04->SetAlbedo("organic_a");
	render_component04->SetNormal("organic_n");
	render_component04->AssignMaterial(textured_material);
	world.SpawnActor(sphere04);
	// - End

	// - Sphere 6
	auto sphere05 = std::make_shared<Sphere>();
	sphere05->transform->location = SimpleMath::Vector3(-60.0, 0.0f, 15.0f);
	sphere05->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);
	auto render_component05 = sphere05->GetComponent<MeshRenderer>();
	render_component05->SetAlbedo("metal_raw_a");
	render_component05->SetNormal("metal_raw_n");
	render_component05->AssignMaterial(textured_chrome_material);
	world.SpawnActor(sphere05);
	// - End

	// SPAWN SOME SHAPES SO THAT WE CAN SIMULATE PHYSX by NVIDIA

	std::vector<std::shared_ptr<Sphere>> physx_spheres = std::vector<std::shared_ptr<Sphere>>(40);

	auto start_location = SimpleMath::Vector3(-60.0, 105.0f, 100.0f);

	float offset = 11.0f;

	for (size_t i = 0; i < physx_spheres.size(); i++)
	{
		physx_spheres[i] = std::make_shared<Sphere>();

		physx_spheres[i]->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);

		physx_spheres[i]->transform->location = start_location;

		physx_spheres[i]->transform->location += SimpleMath::Vector3(i % 5 * offset, i / 5 * (-offset), 0.0f);

		// Add collider component
		auto physx_collider = std::make_shared<SphereCollider>(*physx_spheres[i]);
		physx_spheres[i]->AddComponent<SphereCollider>(physx_collider);

		// Add rigidbody component
		auto physx_rb = std::make_shared<RigidBody>(*physx_spheres[i], 1.0f, eRigidBodyType::DYNAMIC);
		physx_spheres[i]->AddComponent<RigidBody>(physx_rb);

		// assign material
		auto physx_material = physx_spheres[i]->GetComponent<MeshRenderer>();
		physx_material->SetAlbedo("wood_a");
		physx_material->SetNormal("wood_n");
		physx_material->AssignMaterial(textured_chrome_material);

		world.SpawnActor(physx_spheres[i]);
	}
	// - End

	// Create a physical sphere so that we can shoot against other spheres with a rigidbody

	// - Sphere 7
	auto sphere06 = std::make_shared<Sphere>();
	sphere06->transform->location = SimpleMath::Vector3(-45.0, 40.0f, 20.0f);
	sphere06->transform->scale = SimpleMath::Vector3(5.0f, 5.0f, 5.0f);

	auto sphere06_collider = std::make_shared<SphereCollider>(*sphere06);
	sphere06->AddComponent(sphere06_collider);

	auto sphere06_rigidbody = std::make_shared<RigidBody>(*sphere06, 10.0f, eRigidBodyType::DYNAMIC);
	sphere06_rigidbody->SetUseGravity(true);
	sphere06->AddComponent(sphere06_rigidbody);

	auto render_component06 = sphere06->GetComponent<MeshRenderer>();
	render_component06->SetAlbedo("metal_raw_a");
	render_component06->SetNormal("metal_raw_n");
	render_component06->AssignMaterial(textured_chrome_material);
	world.SpawnActor(sphere06);
	// - End*/

	// 2D Quad
	auto quad00 = std::make_shared<Quad>(5.0f, 5.0f);
	quad00->GetComponent<SpriteRenderer>()->SetTexture("grid");

	world.SpawnActor(quad00);

	dx11fw_engine.Run();

	return 0;
}