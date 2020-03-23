#include "Material.h"
#include <iostream>



Material::Material()
{

}

Material::Material(std::string & DiffusePath, std::string & SpecularPath, float specExp, glm::vec3 & hue)
	:specularExponent(specExp), hue(hue)
{
	loadTexture(TextureType::Diffuse, DiffusePath);
	loadTexture(TextureType::Specular, SpecularPath);
}

Material::~Material()
{

}

void Material::loadTexture(TextureType Type, const std::string & TexFile)
{
	switch (Type)
	{
	case TextureType::Diffuse:
		if (!Diffuse.load(TexFile))
		{
			system("pause");
			exit(0);
		}
		break;
	case TextureType::Specular:
		if (!Specular.load(TexFile))
		{
			system("pause");
			exit(0);
		}
		break;

	case TextureType::Normal:
		if (!Normal.load(TexFile))
		{
			system("pause");
			exit(0);
		}
		break;
	default:
	{
		std::cout << "ERROR! TextureType not Found: " << Type << std::endl;
		system("pause");
		exit(0);
	}
		break;
	}
}
