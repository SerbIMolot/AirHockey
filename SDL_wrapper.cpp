#include "stdafx.h"
#include "SDL_wrapper.h"


SDL_Renderer* SDL_wrapper::gRenderer = NULL;

TTF_Font* SDL_wrapper::gFont = nullptr;

SDL_DisplayMode SDL_wrapper::displayMode;


SDL_wrapper::SDL_wrapper()
{

}


SDL_wrapper::~SDL_wrapper()
{
}


bool SDL_wrapper::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;

	}
	else
	{
		if ( SDL_GetDesktopDisplayMode( 0, &displayMode ) != 0)
		{
			success = false;
		}

		//Create window
		gWindow = SDL_CreateWindow("Air Hockey", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayMode.w / 2, displayMode.h / 2, SDL_WINDOW_SHOWN);



		if (gWindow == NULL)
		{

			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;

		}
		else
		{

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}


			int imgFlags = IMG_INIT_PNG;

			if ( !( IMG_Init(imgFlags) & imgFlags ) )
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}

			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
				success = false;

			}

			TimerIns::Instance();
			TextureManager::Initialize();


		}
		

	}

	return success;
}


bool SDL_wrapper::loadMedia()
{
	bool success = true;

	gFont = TTF_OpenFont("Data/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
	}
	return success;
}

void SDL_wrapper::close()
{

	
	TTF_CloseFont(gFont);
	gFont = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

