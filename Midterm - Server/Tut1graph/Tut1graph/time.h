#pragma once


// keep time

class timer {
public:
	timer();
	~timer();

	float tick();
	float getElapsedTimeMS();
	float getElapsedTimeS();
	float getCurrentTime();

private:
	float currentTime, previousTime, elapsedTime;


};