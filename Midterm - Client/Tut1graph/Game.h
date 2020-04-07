#pragma once

#include "time.h"
#include "mesh.h"
#include "Shaders.h"
#include "Light.h"
#include <vector>
#include "Material.h"
#include "Object.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 432
#define FRAMES_PER_SECOND 60
class game {

public:
	game();
	~game();

	void initializeGame();
	void update();
	void draw();
	void LoadTexture(TextureType Type, const std::string &texFile);

	// input

	void keyDown(unsigned char key, int mouseX, int mouseY);
	void keyUP(unsigned char key, int mouseX, int mouseY);
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	
	//data
	timer* updateTimer = nullptr;

	Material mat;
	Mesh monkey;
	Object Paddle;
	Object ball;
	Object wall1;
	Object wall2;
	Object wall3;
	Object wall4;
	Object wall5;
	Object wall6;
	Object wall7;
	Object wall8;
	Object wall9;
	Object wall10;
	Object wall11;
	Object wall12;
	Object background;
	Shader passThrough;
	Shader PhongNoTexture;
	Shader Phong;
	Shader PhongColourSides;
	std::vector<Light> pointLights;
	Light directionalLight;
	std::string clientId;


	bool wall1Spawn = false;
	bool wall2Spawn = false;

	bool wall3Spawn = false;
	bool wall4Spawn = false;

	bool wall5Spawn = false;
	bool wall6Spawn = false;

	bool wall7Spawn = false;
	bool wall8Spawn = false;

	bool wall9Spawn = false;
	bool wall10Spawn = false;

	bool wall11Spawn = false;
	bool wall12Spawn = false;

	bool Spin = false;
	bool shouldLightSpin = false;

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
	glm::mat4 monkeyTransform;
	glm::mat4 ballTransform;
	glm::mat4 paddleTransform;
	glm::mat4 LightSpinner;

};