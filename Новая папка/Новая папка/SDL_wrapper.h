#pragma once



class SDL_wrapper
{
public:
	SDL_Window* gWindow = NULL;

	static SDL_Renderer* gRenderer;

	static TTF_Font* gFont;

	static SDL_DisplayMode displayMode;




	
	//starts SDL and creates window
	bool Init();
	//load media
	bool loadMedia();
	//Frees media and shots down sdl
	void close();

	SDL_Surface* loadSurface(std::string path);

	SDL_Texture* loadTexture(std::string path);

	SDL_wrapper();
	~SDL_wrapper();
};

