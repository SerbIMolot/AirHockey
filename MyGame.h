#pragma once
enum KeyPress {
	KEY_PRESS_DEFAULT,
	KEY_PRESS_UP,
	KEY_PRESS_DOWN,
	KEY_PRESS_LEFT,
	KEY_PRESS_RIGHT,
	KEY_PRESS_TOTAL
};




class MyGame {
public:
	SDL_Window* gWindow = NULL;

	//SDL_Texture* gTexture = NULL;

	static SDL_Renderer* gRenderer;
	/* Animation */
	const int WALKING_ANIMATION_FRAMES = 4;
	std::vector<SDL_Rect> gSpriteClips;

	static TTF_Font* gFont;

	Texture gTextTexture ;
	TextureManager* txtrs = nullptr;
	Camera* cam = nullptr;
	Map* map = nullptr;
	Player* pl = nullptr;
	/*
	Key pressing by KEyStates
	Texture gKeyPressDefault;
	Texture gKeyPressUp;
	Texture gKeyPressDown;
	Texture gKeyPressLeft;
	Texture gKeyPressRight;
	*/
	//Texture gModulatedTexture;
	//Texture gBackgroundTexture;
	/* CLipping and colorKey 
	Texture gFooTexture;
	Texture gBackgroundTexture;
	
	SDL_Rect gSpriteClips[4];
	*/
	//SDL_Surface* gScreenSurface = NULL;
	//SDL_Surface* gHelloWorld = NULL;

	//SDL_Surface* gCurrentSurface = NULL;

	//SDL_Surface* gKeyPress[KEY_PRESS_TOTAL];

//starts SDL and creates window
bool Init();
//load media
bool loadMedia();
//Frees media and shots down sdl
void close();

SDL_Surface* loadSurface(std::string path);

SDL_Texture* loadTexture(std::string path);

MyGame();
~MyGame();
};