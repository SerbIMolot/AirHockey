#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
	: Object()
{

	setSkin(TextureManager::getTexture("Scope.png"), tMouse );
	
	getColShape()->addShape( -10, -10 );

	setMass( 0 );
	
}


Mouse::~Mouse()
{
}

void Mouse::grabObj(std::shared_ptr<Object> obj)
{
	grabbedObj = std::move( obj );
}

void Mouse::releaseObj()
{
	grabbedObj.reset();
}


void Mouse::UpdateStats( int x, int y, bool isReleased, int button )
{
	updatePosition(x, y);

	if ( isReleased == false && button == SDL_BUTTON_LEFT )
	{
		LMBHold = true;
		
	}
	else if ( isReleased == true && button == SDL_BUTTON_LEFT )
	{
		LMBHold = false;

		releaseObj();
	}

	getColShape()->Update( Pos() );
	
}

void Mouse::Update()
{

	if (grabbedObj != nullptr && LMBHold == true)
	{
		grabbedObj->updatePosition( Pos()->getX(), Pos()->getY() );
	}

	if( LMBHold == true )
	{
		std::cout << "LMBHOLD" << std::endl;
	}

	getColShape()->Update( Pos() );


}

void Mouse::Draw()
{
		getSkin()->render( Pos() );

}

void Mouse::collisionDetected( std::shared_ptr < Object > obj )
{

	if( obj->getType() == tPusher )
	{
		grabObj( obj );
	}
}



