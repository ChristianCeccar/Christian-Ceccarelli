#pragma once
#include <glm\glm.hpp>

class Light
{
public:
	Light();
	~Light();

	glm::vec4 PositionorDirection, originalPosition;

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	float SpecularExponent;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;


};