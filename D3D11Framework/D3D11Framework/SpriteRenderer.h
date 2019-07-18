#pragma once

#include <memory>
#include <string>

#include "Component.h"
#include "Core.h"
#include <SimpleMath.h>

class Sprite;
class Actor;
class Texture;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(Actor& owner, float width, float height);

	static unsigned int Type;

	virtual void BeginPlay() override;

	virtual void Tick(float delta_time) override;

	std::shared_ptr<Sprite> sprite;

	void SetColor(const DirectX::SimpleMath::Vector4& color);
	void SetTexture(const std::string& texture_name);

	//todo: implement GetColor() const

private:
	Actor& owner;

	std::shared_ptr<Texture> albedo;
};