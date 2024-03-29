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
	vertices_count = 6;

	float sprite_vertices[] =
	{
		-1, 1, 0,
		1, 1, 0,
		-1, -1, 0,

		1, -1, 0,
		1, 1, 0,
		-1, -1, 0
	};

	float sprite_normals[] =
	{
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};

	float sprite_uvs[] =
	{
		0, 1,
		1, 1,
		0, 0,

		1, 0,
		1, 1,
		0, 0
	};

	PushGPUBuffer(sizeof(sprite_vertices), sizeof(float) * 3, sprite_vertices);
	PushGPUBuffer(sizeof(sprite_normals), sizeof(float) * 3, sprite_normals);
	PushGPUBuffer(sizeof(sprite_uvs), sizeof(float) * 2, sprite_uvs);

	mesh_mvp_buffer = std::make_shared<GPUConstBuffer>(static_cast<unsigned int>(sizeof(Mvp)));

	mesh_position = { 0.0f, 0.0f, 0.0f };
	mesh_rotation = SimpleMath::Quaternion::Identity;
	mesh_scale = { 1.0f * width, 1.0f * height, 1.0f };

	sprite_buffer = {};
	
	in_color = { 1.0f, 1.0f, 1.0f, 1.0f };

	sprite_gpu_buffer = std::make_shared<GPUConstBuffer>(static_cast<unsigned int>(sizeof(SpriteBuffer)));
}

void Sprite::Draw(std::shared_ptr<Texture> texture, std::shared_ptr<Material> material)
{
	Engine::Singleton().GetDxDevice()->SetBlendMode(BlendMode::eTRANSPARENT);

	/*ShaderManager::GetVertexShaderResourceFromMemory("sprite_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("sprite_pixel")->Bind();*/

	if (texture)
		texture->GetShaderObject()->Bind(0);

	sprite_buffer.color = in_color;
	sprite_gpu_buffer->BindInPixel(0, &sprite_buffer, 1);

	MeshShape::DrawMesh(vertices_count);

	if (texture)
		texture->GetShaderObject()->Unbind(0);

	/*ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();*/

	Engine::Singleton().GetDxDevice()->SetBlendMode(BlendMode::eOPAQUE);
}
