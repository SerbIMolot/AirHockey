#pragma once

#include "stdafx.h"

class Timer
{

	//When timer was started
	Uint32 mStartTicks;

	//Amount of ticks when tiemr was paused
	Uint32 mPausedTicks;

	//Timer status
	bool mPaused;
	bool mStarted;


public:
	Timer();
	~Timer();

	//clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Get timers time
	Uint32 getTicks();
	float getSeconds();

	float deltaTime();

	//Check status of timer
	bool isStarted();
	bool isPaused();


};

