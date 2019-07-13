#pragma once

#include "Core.h"

#include <SimpleMath.h>

using namespace DirectX;

struct Material

{
private:
	SimpleMath::Vector4  Emissive;       // 16 bytes
	SimpleMath::Vector4  Ambient;        // 16 bytes
	SimpleMath::Vector4  Diffuse;        // 16 bytes
	SimpleMath::Vector4  Specular;       // 16 bytes
	float SpecularPower;			     // 4 bytes
	BOOL UseTexture;				     // 4 bytes
	BOOL UseNormal;					     // 4 bytes
	float _PAD;						     // 4 bytes

public:
	Material() : Emissive(), Ambient(), Diffuse(), Specular(), SpecularPower(), UseTexture(), UseNormal()
	{

	}

	Material(SimpleMath::Vector4 emissive, SimpleMath::Vector4 ambient, SimpleMath::Vector4 diffuse, SimpleMath::Vector4 specular, float specular_power, BOOL use_texture, BOOL use_normal) :
		Emissive(emissive),
		Ambient(ambient),
		Diffuse(diffuse),
		Specular(specular),
		SpecularPower(specular_power),
		UseTexture(use_texture),
		UseNormal(use_normal)
	{
	}

	// Setters
	void SetEmissive(const SimpleMath::Vector4& emissive);
	void SetAmbient(const SimpleMath::Vector4& ambient);
	void SetDiffuse(const SimpleMath::Vector4& diffuse);
	void SetSpecular(const SimpleMath::Vector4& specular);
	void SetSpecularExponent(float value);
	void SetUseAlbedo(bool value);
	void SetUseNormalMap(bool value);

	// Getters
	const SimpleMath::Vector4& GetEmissive() const;
	const SimpleMath::Vector4& GetAmbient() const;
	const SimpleMath::Vector4& GetDiffuse() const;
	const SimpleMath::Vector4& GetSpecular() const;
	float GetSpecularExponent() const;
	bool GetUseAlbedo() const;
	bool GetUseNormalMap() const;
};