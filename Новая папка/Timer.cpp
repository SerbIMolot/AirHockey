#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}


Timer::~Timer()
{
}

void Timer::start()
{
	//Start timer
	mStarted = true;
	//unpause
	mPaused = false;
	// Get current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	mStarted = false;

	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	if ( mStarted && !mPaused )
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	if ( mStarted && mPaused )
	{
		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPausedTicks;

		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

float Timer::getSeconds()
{
	return static_cast< float >( getTicks() / 1000.f );
}

float Timer::deltaTime()
{

	return 0.0f;
}


bool Timer::isStarted()
{
	return mStarted;
}

bool Timer::isPaused()
{
	return mPaused && mStarted;
}
