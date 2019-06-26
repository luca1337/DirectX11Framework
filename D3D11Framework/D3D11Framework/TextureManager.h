#pragma once

#include <string>
#include <map>

class Texture;

class TextureManager
{
public:
	static void AddTexture(const std::string& path, const std::string& name);
	static std::shared_ptr<Texture> GetTexture(const std::string name);

private:
	static std::map<std::string, std::shared_ptr<Texture>> textures;
};

