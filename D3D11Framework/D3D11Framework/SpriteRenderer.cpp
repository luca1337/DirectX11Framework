#include "SpriteRenderer.h"
#include "Actor.h"
#include "Sprite.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Texture.h"

unsigned int SpriteRenderer::Type = 0;

SpriteRenderer::SpriteRenderer(Actor& owner, float width, float height) : owner(owner)
{
	sprite = std::make_shared<Sprite>(width, height);
}

void SpriteRenderer::BeginPlay()
{
}

void SpriteRenderer::Tick(float delta_time)
{
	// set the transform
	sprite->mesh_position	=	{ owner.transform->location };
	sprite->mesh_rotation	=	{ owner.transform->rotation };
	sprite->mesh_scale		=	{ owner.transform->scale };

	sprite->Draw(albedo);
}

void SpriteRenderer::SetColor(const DirectX::SimpleMath::Vector4 & color)
{
	sprite->in_color = color;
}

void SpriteRenderer::SetTexture(const std::string & texture_name)
{
	albedo = TextureManager::GetTexture(texture_name);
}
