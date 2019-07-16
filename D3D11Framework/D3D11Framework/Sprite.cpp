#include "Sprite.h"
#include "GPUConstBuffer.h"

#include "Device.h"
#include "Engine.h"

#include "ShaderManager.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "ShaderObject.h"
#include "BlendMode.h"

Sprite::Sprite(float width, float height)
{
	float vertices[] =
	{
		-1, 1, 0,
		1, 1, 0,
		-1, -1, 0,

		1, -1, 0,
		1, 1, 0,
		-1, -1, 0
	};

	float normals[] =
	{
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};

	float uvs[] = 
	{
		0, 1,
		1, 1,
		0, 0,

		1, 0,
		1, 1,
		0, 0
	};

	PushGPUBuffer(sizeof(vertices), sizeof(float) * 3, vertices);
	PushGPUBuffer(sizeof(normals), sizeof(float) * 3, normals);
	PushGPUBuffer(sizeof(uvs), sizeof(float) * 2, uvs);

	vertices_count = 6;

	mesh_mvp_buffer = std::make_shared<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<unsigned int>(sizeof(Mvp)));

	mesh_position = { 0.0f, 0.0f, 0.0f };
	mesh_rotation = SimpleMath::Quaternion::Identity;
	mesh_scale = { 1.0f * width, 1.0f * height, 1.0f };

	sprite_buffer = {};

	sprite_gpu_buffer = std::make_shared<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<unsigned int>(sizeof(SpriteBuffer)));
}

void Sprite::Draw()
{
	ShaderManager::GetVertexShaderResourceFromMemory("sprite_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("sprite_pixel")->Bind();

	sprite_buffer.color = {1.0f, 1.0f, 0.0f, 1.0f};
	sprite_buffer.use_texture = 0;

	sprite_gpu_buffer->BindInPixel(0, &sprite_buffer, 1);

	MeshShape::DrawMesh();

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();
}

void Sprite::DrawTextured(std::shared_ptr<Texture> texture)
{
	Engine::Singleton().GetDxDevice()->SetBlendMode(BlendMode::eTRANSPARENT);

	ShaderManager::GetVertexShaderResourceFromMemory("sprite_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("sprite_pixel")->Bind();

	if (texture)
		texture->GetShaderObject()->Bind(0);

	sprite_buffer.use_texture = 1;

	sprite_gpu_buffer->BindInPixel(0, &sprite_buffer, 1);

	MeshShape::DrawMesh();

	if (texture)
		texture->GetShaderObject()->Unbind(0);

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();

	Engine::Singleton().GetDxDevice()->SetBlendMode(BlendMode::eOPAQUE);
}
