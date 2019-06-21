#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

class SDL_wrapper
{
public:
	SDL_Window* gWindow = NULL;

	static SDL_Renderer* gRenderer;

	static SDL_DisplayMode displayMode;

	static void drawRect(std::shared_ptr<Rectangle> rect, const SDL_Color & color);


	
	//starts SDL and creates window
	bool Init();
	//load media
	bool loadMedia();
	
	//Frees media and shots down sdl
	void close();

	SDL_wrapper();
	~SDL_wrapper();
};

