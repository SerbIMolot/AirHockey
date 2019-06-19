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


	Instance()->cursor->Update( x, y, isReleased,  button );

	if (isReleased == false && button == SDL_BUTTON_LEFT )
	{
		mouseHold = true;

		//if( Collisions->collisionCheck( cursor, p1 ) )
		//{
			
		//}
	}
	else if ( isReleased == true && button == SDL_BUTTON_LEFT )
	{
		mouseHold = false;
	}
	//p1->moveTo( p1->Pos()->getX(), p1->Pos()->getY(), x, y );
	//p1->Velocity( x - p1->Pos()->getX(), y - p1->Pos()->getY() );
	
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

	board = std::make_shared< Board >();

	eventHandler = std::make_shared< EventHandle >();

	GameObjects.push_back( p1 );

	GameObjects.push_back( puck );

	Collisions = std::make_shared< Collision >();
	Collisions->addObject( puck );
	Collisions->addObject( p1 );
	Collisions->addObject( enemy );
	
	//Collisions->addObject( cursor );

	

	return 1;

}

void AirHockey::GameTick( )
{


		
		eventHandler->Update();

		puck->Update();
		
		p1->Update();

		if( mouseHold == true  && Collisions->pointCircleCollision( cursor->Pos() , std::static_pointer_cast< Circle >( p1->getColShape()->getFirst() ) ) )
		{
			std::cout << "HOLD" << std::endl;
			//p1->moveTo(p1->Pos()->getX(), p1->Pos()->getY(), cursor->Pos()->getX(), cursor->Pos()->getY());
			p1->moveTo( p1->Pos()->getX(), p1->Pos()->getY(), cursor->Pos()->getX(), cursor->Pos()->getY() );
			//p1->Pos( cursor->Pos()->getX(), cursor->Pos()->getY() );
		}

		enemy->Update();

		Collisions->Update();
		
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



