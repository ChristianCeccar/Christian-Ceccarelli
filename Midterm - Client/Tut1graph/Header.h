#pragma once
#include "time.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Light.h"
#include <vector>
#include "Material.h"
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
	void loadTexture(const std::string &text);
	

	// input

	void keyDown(unsigned char key, int mouseX, int mouseY);
	void keyUP(unsigned char key, int mouseX, int mouseY);
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);

	timer* updateTimer = nullptr;

	TextureType type;
	Texture texture;
	Material mat;
	Mesh monkey;
	Mesh Cube;
	ShaderProgram passThrough;
	ShaderProgram phongNoTexture;
	ShaderProgram phong;
	ShaderProgram phongColorSides;
	std::vector<Light>pointLights;
	Light directionalLight;

	glm::mat4 lightSpinner;
	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
	glm::mat4 monkeyTransform;
private:
	bool shouldLightSpin = false;
};