#include "stdafx.h"
#include "AirHockey.h"

EventHandle::EventHandle()
{
}


EventHandle::~EventHandle()
{
}

void EventHandle::Update()
{
	while (SDL_PollEvent(&e) != 0)
	{

		//uset request quit
		if (e.type == SDL_QUIT)
		{

			AirHockey::quit = true;
			
		}
		
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			bool isReleased = false;

			if ( e.type == SDL_MOUSEBUTTONDOWN )
			{
				isReleased = false;
				
			}
			else if ( e.type == SDL_MOUSEBUTTONUP )
			{
				isReleased = true;
			}

			AirHockey::Instance()->onMouseButtonEvent(e.motion.x, e.motion.y, isReleased, e.button.button);
		}

		const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);

		if (currentKeyState[SDL_SCANCODE_LEFT])
		{

		}

		if (currentKeyState[SDL_SCANCODE_RIGHT])
		{
		}
		switch (e.type) {

		case SDLK_UP:

			break;

		case SDLK_DOWN:

			break;

		case SDLK_LEFT:

			break;

		case SDLK_RIGHT:

			break;

		default:

			break;
		}

	}

}
