#pragma once
#include "stdafx.h"
#include "EventHandle.h"



class AirHockey{
	
public:

	static std::vector< std::shared_ptr< Object > > GameObjects;
	static std::shared_ptr< EventHandle > eventHandler;
	static std::unique_ptr<SDL_wrapper> Game;
	static std::shared_ptr<AirHockey> hInstance;

	static bool quit;

	std::shared_ptr< Collision > Collisions;

	std::shared_ptr< Mouse > cursor;
	std::shared_ptr< Pusher > p1;
	std::shared_ptr< Puck > puck;
	std::shared_ptr< Enemy > enemy;
	//static std::shared_ptr<Button > startButton;
	std::shared_ptr< Board > board;

	bool mouseHold;



	AirHockey();
	~AirHockey();
	 SDL_Event e;
	


	static std::shared_ptr<AirHockey> Instance();
	
	void GameDraw();
	
	bool GameInit();
	
	void GameTick( );

	void GameReset();
	
	void onMouseButtonEvent(int x, int y, bool isReleased, int button);

};

