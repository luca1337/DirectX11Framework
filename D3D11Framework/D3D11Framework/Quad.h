#pragma once

#include "Actor.h"

#include "Core.h"
#include <SimpleMath.h>
#include <string>

class SpriteRenderer;

class Quad : public Actor
{
public:
	Quad(float width, float height)
	{
		sprite_renderer = std::make_shared<SpriteRenderer>(*this, width, height);
		AddComponent<SpriteRenderer>(sprite_renderer);

		transform->scale = { width, height, 1 };
	}

private:
	std::shared_ptr<SpriteRenderer> sprite_renderer;
};