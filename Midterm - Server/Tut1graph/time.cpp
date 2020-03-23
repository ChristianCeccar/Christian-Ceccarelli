#include "time.h"
#include <GL\glut.h>

timer::timer() {
	previousTime = glutGet(GLUT_ELAPSED_TIME);
	tick();

};
timer::~timer() {};

float timer::tick() {
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - previousTime;
	previousTime = currentTime;

	return elapsedTime;
};
float timer::getElapsedTimeMS() {
	return elapsedTime;
};
float timer::getElapsedTimeS() {
	return elapsedTime / 1000.0f;
};
float timer::getCurrentTime() {
	return currentTime;
};