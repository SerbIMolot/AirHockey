// AirHockey.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

bool AirHockey::quit = false;
std::unique_ptr<SDL_wrapper> AirHockey::Game = std::make_unique<SDL_wrapper>();
std::shared_ptr< AirHockey > AirHockey::hInstance(nullptr);
std::vector< std::shared_ptr< Object > > AirHockey::GameObjects;
std::shared_ptr< EventHandle > AirHockey::eventHandler = std::make_shared< EventHandle >();

void AirHockey::onMouseButtonEvent( int x, int y, bool isReleased, int button )
{


	Instance()->cursor->UpdateStats( x, y, isReleased,  button );

	//p1->updatePosition( x, y );

	
}


AirHockey::AirHockey()
{


}

AirHockey::~AirHockey()
{
}

std::shared_ptr<AirHockey> AirHockey::Instance()
{
	if ( !hInstance )
	{
		hInstance = std::make_unique< AirHockey >();
	}
	return hInstance ;
}

void AirHockey::GameDraw()
{
	SDL_SetRenderDrawColor(SDL_wrapper::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(SDL_wrapper::gRenderer);

	p1->Draw();
	puck->Draw();
	enemy->Draw();
	
	board->Draw();


	SDL_RenderPresent(SDL_wrapper::gRenderer);
}

bool AirHockey::GameInit()
{

	AirHockey::Instance();
	

	if ( !Game->Init() )
	{

		printf("Failed to initialize!\n");

		return 0;

	}

	if ( !Game->loadMedia() )
	{

		printf("Failed to load media!\n");

		return 0;

	}
	

	p1 = std::make_shared< Pusher >();
	cursor = std::make_shared< Mouse >();
	puck = std::make_shared< Puck >();
	enemy = std::make_shared< Enemy >();
	enemy->setPuck( puck );

	eventHandler = std::make_shared< EventHandle >();
	board = std::make_shared< Board >();
	GameObjects.push_back( p1 );

	GameObjects.push_back( puck );

	TriggersManager::Instance();


	Collisions = std::make_shared< Collision >();
	Collisions->addObject( puck );
	Collisions->addObject( p1 );
	Collisions->addObject( enemy );
	
	Collisions->addObject( cursor );

	

	return 1;

}

void AirHockey::GameTick( )
{

		
		eventHandler->Update();



		puck->Update();
		
		cursor->Update();

		p1->Update();

		enemy->Update();

		

		Collisions->Update();
		
}

void AirHockey::GameReset()
{
	p1->Pos( SCREEN_WIDTH  / 4, SCREEN_HEIGHT / 2 );
	p1->Velocity( 0, 0 );
	p1->Acceleration( 0, 0 );

	enemy->Pos( SCREEN_WIDTH / 2 + SCREEN_WIDTH / 3 , SCREEN_HEIGHT / 2);
	enemy->Velocity(0, 0);
	enemy->Acceleration(0, 0);

	puck->Pos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	puck->Velocity(0, 0);
	puck->Acceleration(0, 0);
	
}


int main( int argc, char *argv[] )
{
	
	if ( AirHockey::Instance()->GameInit() )
	{
		TimerIns::Instance()->Reset();
	
		while (!AirHockey::Instance()->quit)
			{
				
				TimerIns::Instance()->Update();
				

				AirHockey::Instance()->GameTick();


				AirHockey::Instance()->GameDraw();



			}

		

	}

	

	AirHockey::Instance()->Game->close();
	
		return 0;
}



