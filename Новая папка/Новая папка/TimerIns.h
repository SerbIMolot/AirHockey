#ifndef TIMER_H
#define TIMER_H

#include "stdafx.h"

class TimerIns {
	
	static std::shared_ptr< TimerIns > tInstance;

	unsigned int startTick;
	unsigned int elapsedTicks;
	unsigned int lastTick;
	
	unsigned int deltaTime;
	float timeScale;




public:

	TimerIns();
	~TimerIns();

	static std::shared_ptr< TimerIns > Instance();
	static void Release();

	void Reset();
	unsigned int DeltaTime();
	float DeltaTimeS();

	void TimeScale(float t);
	float TimeScale();

	unsigned int ElapsTicks();

	void Update();

};

#endif
