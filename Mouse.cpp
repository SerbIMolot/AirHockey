#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
	: Object()
{

	setSkin(TextureManager::getTexture("Scope.png"), tMouse );

	setMass( 0 );
	
}


Mouse::~Mouse()
{
}


void Mouse::Update( int x, int y, bool isReleased, int button )
{
	updatePosition(x, y);
	
}

void Mouse::Draw()
{
		getSkin()->render( Pos() );

}

void Mouse::collisionDetected( std::shared_ptr < Object > obj )
{
}



