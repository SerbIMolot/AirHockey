#include "stdafx.h"
#include "Board.h"

int Board::aiPoints = 0;
int Board::playerPoints = 0;

Board::Board()
{
	topWall = std::make_shared< Wall >( 0.0f, 0.0f, TextureManager::getTexture( "wall.png" ) );

	leftWall = std::make_shared< Wall >( 0, 0, TextureManager::getTexture( "plWall.png" ) );

	bottomWall = std::make_shared< Wall >( 0 , SCREEN_HEIGHT - TextureManager::getTexture("wall.png")->getHeight(), TextureManager::getTexture( "wall.png" ) );

	rightWall  = std::make_shared< Wall >( SCREEN_WIDTH - TextureManager::getTexture("enWall.png")->getWidth(), 
										   SCREEN_HEIGHT - TextureManager::getTexture("enWall.png")->getHeight(), TextureManager::getTexture( "enWall.png") );

	redFont = std::make_unique< NFont >( SDL_wrapper::gRenderer, "Data/FreeSans.ttf", 60, NFont::Color( 225, 0, 0, 255) );

	blueFont = std::make_unique< NFont >( SDL_wrapper::gRenderer, "Data/FreeSans.ttf", 60, NFont::Color( 0, 0, 255, 255) );

	//fFont = std::make_unique< FC_Font >( FC_CreateFont() );
	//fFont = FC_CreateFont();

	//FC_LoadFont( fFont, SDL_wrapper::gRenderer, "Data/FreeSans.ttf", 20, FC_MakeColor(255, 0, 0, 255), TTF_STYLE_NORMAL);

	Collision::addObject( topWall );
	Collision::addObject( leftWall );
	Collision::addObject( bottomWall );
	Collision::addObject( rightWall );


	std::shared_ptr< Object > playerGates;
	std::shared_ptr< Object > aiGates;
}


Board::~Board()
{
}


void Board::Draw()
{
	topWall->Draw();
	leftWall->Draw();
	bottomWall->Draw();
	rightWall->Draw();

	redFont->draw(SDL_wrapper::gRenderer, SCREEN_WIDTH / 2 + 30, 10, std::to_string( aiPoints ).c_str()  );

	blueFont->draw(SDL_wrapper::gRenderer, SCREEN_WIDTH / 2 - 60, 10, std::to_string( playerPoints ).c_str() );

//	FC_Draw( fFont, SDL_wrapper::gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "START" );

	TextureManager::getTexture("plGate.png")->render( 0, 168 );

	TextureManager::getTexture("enGate.png")->render(SCREEN_WIDTH - 45, 168);
}