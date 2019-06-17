//#include "inc.h"
#include "stdafx.h"


std::shared_ptr< TimerIns > TimerIns::tInstance = nullptr;

std::shared_ptr< TimerIns > TimerIns::Instance() {
	if (tInstance == nullptr) {
		tInstance = std::make_shared< TimerIns >();
	}

	return tInstance;
}

void TimerIns::Release() {

	tInstance = nullptr;

}

void TimerIns::Reset() 
{

	startTick = SDL_GetTicks();

	elapsedTicks = 0;

	deltaTime = 0.0f;

}

float TimerIns::DeltaTime() 
{
	return deltaTime;
}

void TimerIns::TimeScale(float t) 
{
	timeScale = t;
}

float TimerIns::TimeScale() 
{
	return timeScale;
}

unsigned int TimerIns::ElapsTicks() 
{
	return elapsedTicks;
}

void TimerIns::Update() 
{


	deltaTime = SDL_GetTicks() - lastTick;

	lastTick = SDL_GetTicks();

}

TimerIns::TimerIns() 
{
	Reset();
	timeScale = 1.0f;
}

TimerIns::~TimerIns() 
{
Release();
}