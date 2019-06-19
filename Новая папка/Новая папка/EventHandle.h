#pragma once

#include "stdafx.h"

enum MouseB
{
	mLeft,
	mRight,
	mWheel
};

class EventHandle
{
	SDL_Event e;
public:
	EventHandle();
	~EventHandle();


	void Update();
};

