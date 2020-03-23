#pragma once

#include <iostream>
#include "mesh.h"
#include "Shaders.h"
#include <vector>
#include "Light.h"
#include "Material.h"

#include <GLM/glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <GLM\gtc\type_ptr.hpp>



class Object
{
public:
	Object();
	~Object();

	Object* m_pParent;
	std::vector<Object*> children;

	bool rotXZ = true;
	//sort of constructor to use after actual construction
	void construct(std::string n, std::string file);
	void load();
	void unload();
	void addChild(Object* newChild);
	void removeChild(Object* rip);
	void setLocalPosition(glm::vec3 newPosition);
	void setLocalRotationAngleX(float newAngle);
	void setLocalRotationAngleY(float newAngle);
	void setLocalRotationAngleZ(float newAngle);
	void setLocalScale(float newScale);
	void setLocalScaleX(float newScale);
	void setLocalScaleY(float newScale);
	void setLocalScaleZ(float newScale);
	virtual void update(float dt);
	void setShader(Shader &s, glm::mat4 cameraProjection, glm::mat4 cameraTransform, std::vector<Light>lights, Light directionalLight);
	void drawKinematicLinkage();

	Material mat;

	bool collision(Object &col);
	bool Roofcollision(Object &col);

	glm::vec3 getLocalPosition();

	glm::mat4 getLocalToWorldMatrix();

	glm::vec3 getWorldPosition();

	glm::mat4 getWorldRotation();

	std::vector<Object*> getChildren();

	Object* getParent();

	float getLocalScale();
	float getLocalRotationAngleX();
	float getLocalRotationAngleY();
	float getLocalRotationAngleZ();

	std::string getName();
	Mesh getMesh();

	float rotX, rotY, rotZ;
	float scale;



	float XHelp = 1.f, ZHelp = 1.f;
	//glm::mat4 Transform;
	//glm::mat4 Translate;
	//glm::mat4 Rotate;
	glm::vec3 Position;
	//glm::vec3 View;

	glm::vec3 localPosition;
	glm::mat4 localRotation;
	glm::mat4 localTransformMatrix;
	glm::mat4 localToWorldMatrix;

	//glm::vec3 getPosition();

	std::string name;
	std::string filePath;
private:
	Mesh mesh;

};

