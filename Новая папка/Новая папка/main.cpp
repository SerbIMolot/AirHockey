#include "stdafx.h"

#define FPS_LIMIT 60
#define TICKS_PER_FRAME 1000 / FPS_LIMIT



int main(int argc, char* argv[])
{
	MyGame* Game = new MyGame();
	
	bool quit = false;

	SDL_Event e;

	int frame = 0;

	double degrees = 0;
	std::stringstream timeText;
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };
	//Texture* currentTexture = nullptr;

	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	Timer fpsTimer;
	Timer capTimer;
	int countedFrames = 0;

	TextureManager::addText("YOU SHALL PASS");

	fpsTimer.start();

	//Uint8 alpha = 255;

	//Start SDL and create window
	if (!Game->Init())
	{

		printf("Failed to initialize!\n");

	}
	else
	{
		//load media
		if (!Game->loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			
			Game->cam->setPlayer(Game->pl);
			//Game->gCurrentSurface = Game->gKeyPress[KEY_PRESS_DEFAULT];
			
			while (!quit)
			{

				capTimer.start();
				//Handle event on queue
				while (SDL_PollEvent(&e) != 0)
				{
					Game->pl->handleEvent(e);
					//uset request quit
					if (e.type == SDL_QUIT)
					{

						quit = true;
						//IF KEY PRESSED
					}
					const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
					if (currentKeyState[SDL_SCANCODE_LEFT])
					{

					}

					if (currentKeyState[SDL_SCANCODE_RIGHT])
					{
					}
					/*
					//set texture based on keystate
					const Uint8* currentKeyState = SDL_GetKeyboardState( NULL ) ;

					if (currentKeyState[SDL_SCANCODE_UP])
					{
					currentTexture = &Game->gKeyPressUp;
					}
					else if (currentKeyState[SDL_SCANCODE_DOWN])
					{
					currentTexture = &Game->gKeyPressDown;
					}
					else if (currentKeyState[SDL_SCANCODE_LEFT])
					{
					currentTexture = &Game->gKeyPressLeft;
					}
					else if (currentKeyState[SDL_SCANCODE_RIGHT])
					{
					currentTexture = &Game->gKeyPressRight;
					}
					else
					{
					currentTexture = &Game->gKeyPressDefault;
					}
					*/
					/*
					keyhandeling based on keydown

					else if (e.type == SDL_KEYDOWN)
					{

					//WHAT KEY WAS PRESSED
					switch (e.key.keysym.sym)
					{
					modulated texure
					case SDLK_s:
					if ( alpha - 32 < 0 )
					{
					alpha = 0;

					}
					else
					{
					alpha -= 32;

					}

					break;
					case SDLK_w:
					if ( alpha + 32 > 255 )
					{
					alpha = 255;
					}
					else
					{
					alpha += 32;
					}

					//Increase red
					case SDLK_q:
					red += 32;
					break;

					//Increase green
					case SDLK_w:
					green += 32;
					break;

					//Increase blue
					case SDLK_e:
					blue += 32;
					break;

					//Decrease red
					case SDLK_a:
					red -= 32;
					break;

					//Decrease green
					case SDLK_s:
					green -= 32;
					break;

					//Decrease blue
					case SDLK_d:
					blue -= 32;
					break;


					case SDLK_a:
					degrees -= 60;
					break;

					case SDLK_d:
					degrees += 60;
					break;

					case SDLK_q:
					flipType = SDL_FLIP_HORIZONTAL;
					break;

					case SDLK_w:
					flipType = SDL_FLIP_NONE;
					break;

					case SDLK_e:
					flipType = SDL_FLIP_VERTICAL;
					break;

					case SDLK_UP:
					//Game->gCurrentSurface = Game->gKeyPress[KEY_PRESS_UP];
					break;

					case SDLK_DOWN:
					//Game->gCurrentSurface = Game->gKeyPress[KEY_PRESS_DOWN];
					break;

					case SDLK_LEFT:
					//Game->gCurrentSurface = Game->gKeyPress[KEY_PRESS_LEFT];
					break;

					case SDLK_RIGHT:
					//Game->gCurrentSurface = Game->gKeyPress[KEY_PRESS_RIGHT];
					break;

					default:
					//Game->gCurrentSurface = Game->gKeyPress[KEY_PRESS_DEFAULT];
					break;
					}
					}
					*/
				}

				float avgFPS = countedFrames / fpsTimer.getSeconds();

				if (avgFPS > 200000)
				{
					avgFPS = 0;
				}

				timeText.str("");
				timeText << "Average fps: " << avgFPS;
				if (!Game->gTextTexture.loadFromText(timeText.str().c_str(), textColor))
				{
					printf("Unable to render fps texture!\n");
				}


				SDL_SetRenderDrawColor(Game->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Game->gRenderer);

				SDL_Rect r;
				r.x = 50;
				r.y = 50;
				r.h = 50;
				r.w = 50;

				SDL_SetRenderDrawColor( Game->gRenderer, 0, 0, 255, 255 );

				


				
				Game->pl->Update();
				Game->cam->Update();
				Game->map->draw();

				Game->gTextTexture.render((SCREEN_WIDTH - Game->gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - Game->gTextTexture.getHeight()) / 2);
				Game->pl->Draw();
				//currentTexture->render(0,0);
				//Game->gArrowTexture.render((SCREEN_WIDTH - Game->gArrowTexture.getWidth()) / 2, (SCREEN_HEIGHT - Game->gArrowTexture.getHeight()) / 2, NULL, degrees, NULL, flipType );
				SDL_RenderFillRect(Game->gRenderer, &r);

				TextureManager::getTexture("YOU").get()->render(100, 100);
				SDL_RenderPresent(Game->gRenderer);
				countedFrames++;

	
				/* modulated texure
				SDL_SetRenderDrawColor( Game->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear( Game->gRenderer );

				Game->gBackgroundTexture.render( 0, 0 );

				Game->gModulatedTexture.setAlpha( alpha );
				Game->gModulatedTexture.render( 0, 0 );
				*/
				/* clipp and setColor
				//CREAR SCREEN
				SDL_SetRenderDrawColor( Game->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( Game->gRenderer );

				Game->gFooTexture.setColor( red, green, blue );

				Game->gBackgroundTexture.render( 0, 0 );

				Game->gFooTexture.render(0, 0, &Game->gSpriteClips[ 0 ]);
				Game->gFooTexture.render(SCREEN_WIDTH - Game->gSpriteClips[ 1 ].w, 0, &Game->gSpriteClips[ 1 ]);
				Game->gFooTexture.render(0, SCREEN_HEIGHT - Game->gSpriteClips[ 2 ].h, &Game->gSpriteClips[ 2 ]);
				Game->gFooTexture.render(SCREEN_WIDTH - Game->gSpriteClips[ 3 ].w, SCREEN_HEIGHT - Game->gSpriteClips[ 3 ].h, &Game->gSpriteClips[ 3 ]);
				*/

				/* Animation
				SDL_SetRenderDrawColor(Game->gRenderer, 0xff, 0xff, 0xff, 0xff);
				SDL_RenderClear(Game->gRenderer);

				SDL_Rect* CurrentClip = &Game->gSpriteClips[ frame / 4 ];
				Game->gSpriteSheetTexture.render( ( SCREEN_WIDTH - CurrentClip->w ) / 2, ( SCREEN_HEIGHT - CurrentClip->h ) / 2, CurrentClip );
				//Render renderer
				SDL_RenderPresent( MyGame::gRenderer );


				frame++;

				if (frame / 4 >= Game->WALKING_ANIMATION_FRAMES)
				{
				frame = 0;
				}
				*/
				/*
				//Apply the image
				//SDL_BlitSurface(Game->gCurrentSurface, NULL, Game->gScreenSurface, NULL);
				SDL_SetRenderDrawColor(Game->gRenderer, 0xff, 0xff, 0xff, 0xff);

				SDL_RenderClear( Game->gRenderer );

				//Render red filled quad
				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

				SDL_SetRenderDrawColor( Game->gRenderer, 0xFF, 0x00, 0x00, 0xFF );

				SDL_RenderFillRect( Game->gRenderer , &fillRect);

				//Render green outlined quad

				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };

				SDL_SetRenderDrawColor( Game->gRenderer, 0x00, 0xFF, 0x00, 0xFF );

				SDL_RenderDrawRect( Game->gRenderer, &outlineRect );

				//Draw blue horizontal line
				SDL_SetRenderDrawColor( Game->gRenderer, 0x00, 0x00, 0xFF, 0xFF );

				SDL_RenderDrawLine( Game->gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);


				//Draw blue horizontal line
				SDL_SetRenderDrawColor(Game->gRenderer, 0x00, 0x00, 0xFF, 0xFF);

				SDL_RenderDrawLine( Game->gRenderer, SCREEN_WIDTH / 2, 0 , SCREEN_WIDTH / 2, SCREEN_HEIGHT );

				//SDL_RenderPresent( Game->gRenderer );

				SDL_SetRenderDrawColor( Game->gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
				for (int i = 0; i < SCREEN_HEIGHT; i += 4)
				{
				SDL_RenderDrawPoint( Game->gRenderer, SCREEN_WIDTH / 2 + 100, i );
				}
				SDL_SetRenderDrawColor( Game->gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
				for (int i = 0; i < SCREEN_HEIGHT; i += 4)
				{
				SDL_RenderDrawPoint( Game->gRenderer, SCREEN_WIDTH / 2 - 100, i );
				}
				*/
				/*
				//Viev port
				SDL_Rect TopLeftVievPort = { 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

				SDL_RenderSetViewport( Game->gRenderer, &TopLeftVievPort );

				SDL_RenderCopy( Game->gRenderer, Game->gTexture, NULL, NULL );

				SDL_Rect TopRightViewport = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

				SDL_RenderSetViewport( Game->gRenderer, &TopRightViewport );

				SDL_RenderCopy( Game->gRenderer, Game->gTexture, NULL, NULL );

				SDL_Rect bottomview = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };

				SDL_RenderSetViewport(Game->gRenderer, &bottomview);

				SDL_RenderCopy(Game->gRenderer, Game->gTexture, NULL, NULL);

				SDL_RenderPresent( Game->gRenderer );
				*/


				/* APPLY TEXTURE ON SCREEN
				SDL_RenderClear(Game->gRenderer);

				SDL_RenderCopy(Game->gRenderer, Game->gTexture, NULL, NULL);

				SDL_RenderPresent(Game->gRenderer);
				*/
				//SDL_UpdateWindowSurface(Game->gWindow);

				int frameTicks = capTimer.getTicks();
				if ( frameTicks < TICKS_PER_FRAME )
				{
					SDL_Delay( TICKS_PER_FRAME - frameTicks );
				}
			}

		}

	}

	Game->close();
	delete Game;
	return 0;
}