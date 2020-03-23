#include "Game.h"
#include <iostream>
#include <GL\glut.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

game::game()
{

};
game::~game() 
{
	delete updateTimer;
	passThrough.unload();
	PhongNoTexture.unload();
	monkey.unload();
};

void game::initializeGame() {
	updateTimer = new timer();
	glEnable(GL_DEPTH_TEST);
	if (!passThrough.Load("shaders/passthrough.vert", "shaders/passthrough.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}
	if (!PhongNoTexture.Load("shaders/Phong.vert", "shaders/PhongNoTexture.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}
	if (!monkey.loadFromFile("meshes/Monkey.obj"))
	{
		std::cout << "Model failedto load" << std::endl;
		system("pause");
		exit(0);
	}
	cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, -5.f));
	cameraProjection = glm::perspective(45.f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,0.1f , 10000.f);
	


};
void game::update() {
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeS();
	monkeyTransform = glm::rotate(monkeyTransform, deltaTime*(glm::pi<float>() / 4.0f), glm::vec3(0.f, 1.0f, 0.f));
};
void game::draw() 
{

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render
	PhongNoTexture.bind();
	PhongNoTexture.sendUniformMat4("uModel", glm::value_ptr(monkeyTransform), false);
	PhongNoTexture.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	PhongNoTexture.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);

	PhongNoTexture.sendUniform("lightPos", cameraTransform * glm::vec4(4.f,0.f,0.f,1.f));

	PhongNoTexture.sendUniform("objectColour",glm::vec4(0.f, 1.f, 0.f, 1.f));

	PhongNoTexture.sendUniform("lightAmbient", glm::vec3(0.15f, 0.15f, 0.15f));
	PhongNoTexture.sendUniform("lightDiffuse", glm::vec3(0.7f, 0.7f, 0.7f));
	PhongNoTexture.sendUniform("lightSpecular", glm::vec3(1.f, 1.f, 1.f));

	PhongNoTexture.sendUniform("lightSpecularExponenet", 50.f);

	PhongNoTexture.sendUniform("attenuationConstant", 1.f);
	PhongNoTexture.sendUniform("attenuationLinear", 0.1f);
	PhongNoTexture.sendUniform("attenuationQuadratic", 0.01f);

	
	glBindVertexArray(monkey.vao);
	glDrawArrays(GL_TRIANGLES, 0, monkey.getNumVertices());
	glBindVertexArray(GL_NONE);

	PhongNoTexture.unbind();

	glutSwapBuffers();
};

// input

void game::keyDown(unsigned char key, int mouseX, int mouseY) {

	switch (key) {
	case 27:
	case 'q':
		exit(1);
		break;
	case 't':
		std::cout << "total: " 
			<< updateTimer->getCurrentTime() / 1000.0f << std::endl;
	defaut:
		break;
	
	}

};
void game::keyUP(unsigned char key, int mouseX, int mouseY) {
	switch (key) {
	default:
		break;
	
	}

};
void game::mouseClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
		}
	
	}


};
void game::mouseMove(int x, int y) {


};