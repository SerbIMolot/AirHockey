#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	topWall = std::make_shared< Wall >( SDL_wrapper::displayMode.w / 4, 0, TextureManager::getTexture( "wall.png" ) );
	leftWall = std::make_shared< Wall >( 0, SDL_wrapper::displayMode.h / 4, TextureManager::getTexture( "plWall.png" ) );
	bottomWall = std::make_shared< Wall >( SDL_wrapper::displayMode.w / 4, SDL_wrapper::displayMode.h / 2, TextureManager::getTexture( "wall.png" ) );
	rightWall  = std::make_shared< Wall >( SDL_wrapper::displayMode.w / 2, SDL_wrapper::displayMode.h / 4, TextureManager::getTexture( "enWall.png") );

	Collision::addObject( topWall );
	Collision::addObject( leftWall );
	Collision::addObject( bottomWall );
	Collision::addObject( rightWall );

	aiPoints = 0;
	playerPoints = 0;

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
}