#include "Material.h"

// -- SETTERS -- //

void Material::SetEmissive(const SimpleMath::Vector4 & emissive)
{
	Emissive = emissive;
}

void Material::SetAmbient(const SimpleMath::Vector4 & ambient)
{
	Ambient = ambient;
}

void Material::SetDiffuse(const SimpleMath::Vector4 & diffuse)
{
	Diffuse = diffuse;
}

void Material::SetSpecular(const SimpleMath::Vector4 & specular)
{
	Specular = specular;
}

void Material::SetSpecularExponent(const float value)
{
	SpecularPower = value;
}

void Material::SetUseAlbedo(const bool value)
{
	UseTexture = value;
}

void Material::SetUseNormalMap(const bool value)
{
	UseNormal = value;
}

// -- GETTERS -- //

const SimpleMath::Vector4& Material::GetEmissive() const
{
	return Emissive;
}

const SimpleMath::Vector4& Material::GetAmbient() const
{
	return Ambient;
}

const SimpleMath::Vector4& Material::GetDiffuse() const
{
	return Diffuse;
}

const SimpleMath::Vector4& Material::GetSpecular() const
{
	return Specular;
}

float Material::GetSpecularExponent() const
{
	return SpecularPower;
}

bool Material::GetUseAlbedo() const
{
	return UseTexture;
}

bool Material::GetUseNormalMap() const
{
	return UseNormal;
}
