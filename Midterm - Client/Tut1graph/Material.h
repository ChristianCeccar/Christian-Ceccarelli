#pragma once
#include <glm\glm.hpp>
#include "Texture.h"

class Material
{
public:
	Material();
	Material(std::string &DiffusePath, std::string &SpecularPath, float specExp = 50.f, glm::vec3 &hue = glm::vec3(1.f, 1.f, 1.f));

	~Material();

	void loadTexture(TextureType, const std::string &TexFile);

	//Data members
	Texture Diffuse;
	Texture Specular;
	Texture Normal;
	glm::vec3 hue = glm::vec3(1.f, 1.f, 1.f);
	float specularExponent = 50.f;
};