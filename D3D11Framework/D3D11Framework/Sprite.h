#pragma once

#include "MeshShape.h"
#include "SpriteBuffer.h"

#include <string>
#include <memory>

class Texture;
struct Material;

class Sprite : public MeshShape
{
public:
	Sprite(float width = 1.0f, float height = 1.0f);

	void Draw(std::shared_ptr<Texture> texture, std::shared_ptr<Material> material = nullptr);

	unsigned int vertices_count;

private:
	SpriteBuffer sprite_buffer;
	std::shared_ptr<GPUConstBuffer> sprite_gpu_buffer;
	float width;
	float height;
	DirectX::SimpleMath::Vector4 in_color;

	friend class SpriteRenderer;
};