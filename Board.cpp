#include "stdafx.h"
#include "Board.h"

int Board::aiPoints = 0;
int Board::playerPoints = 0;

Board::Board()
{
	topWall = std::make_shared< Wall >( SCREEN_WIDTH / 2, 0, TextureManager::getTexture( "wall.png" ) );
	leftWall = std::make_shared< Wall >( 0, SCREEN_HEIGHT / 2, TextureManager::getTexture( "plWall.png" ) );
	bottomWall = std::make_shared< Wall >( SCREEN_WIDTH / 2, SCREEN_HEIGHT, TextureManager::getTexture( "wall.png" ) );
	rightWall  = std::make_shared< Wall >( SCREEN_WIDTH, SCREEN_HEIGHT / 2, TextureManager::getTexture( "enWall.png") );

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
}