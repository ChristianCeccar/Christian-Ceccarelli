#pragma once

#include "time.h"
#include "mesh.h"
#include "Shaders.h"
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

	// input

	void keyDown(unsigned char key, int mouseX, int mouseY);
	void keyUP(unsigned char key, int mouseX, int mouseY);
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	
	//data
	timer* updateTimer = nullptr;
	Mesh monkey;
	Shader passThrough;
	Shader PhongNoTexture;

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
	glm::mat4 monkeyTransform;
};