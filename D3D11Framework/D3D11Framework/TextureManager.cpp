#include "TextureManager.h"
#include "Texture.h"

std::map<std::string, std::shared_ptr<Texture>> TextureManager::textures;

void TextureManager::AddTexture(const std::string & path, const std::string & name)
{
	auto It = textures.find(name);

	if (It != textures.end())
	{
		throw std::exception("element already exists in memory, please consider using GetTexture() method to retrieve it instead.");
	}

	std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);

	textures.emplace(name, texture);
}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::string name)
{
	std::shared_ptr<Texture> texture;

	for (auto&[key, val] : textures)
	{
		if (key == name)
		{
			texture = textures.at(name);
			break;
		}
	}

	return texture;
}
