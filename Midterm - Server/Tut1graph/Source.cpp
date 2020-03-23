#include<GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Header.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 432
#define FRAMES_PER_SECOND 60

const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

game* game1;
void DisplayCallbackFunction(void) {

	game1->draw();
};

void keyCallbackFunction(unsigned char key, int x, int y) {
	game1->keyDown(key, x, y);
};
void keyUpCallbackFunction(unsigned char key, int x, int y) {
	game1->keyUP(key, x, y);
};
void timerCallbackFunction(int value) {
	game1->update();

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY, timerCallbackFunction, 0);

};

void mouseClickCallbackFunction(int button, int state, int x, int y) {
	game1->mouseClick(button, state, x, y);
}
void mouseMoveCallbackFunction(int x, int y) {  
	game1->mouseMove(x, y);
};

int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Game");

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW could not be initialized" << std::endl;
		system("PAUSE");
		return 0;
	}

	//callback
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(keyCallbackFunction);
	glutKeyboardUpFunc(keyUpCallbackFunction);
	glutMouseFunc(mouseClickCallbackFunction);
	glutMotionFunc(mouseMoveCallbackFunction);
	glutTimerFunc(1, timerCallbackFunction, 0);

	game1 = new game();
	game1->initializeGame();

	//start
	glutMainLoop();

	system("pause");
	return 0;
}