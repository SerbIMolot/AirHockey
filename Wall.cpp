#include "stdafx.h"
#include "Wall.h"


Wall::Wall(std::shared_ptr<Vector2d> vec, std::shared_ptr<Rectangle> rect)
{
	Velocity(0, 0);

	
	Pos( vec );
	setMass(100);
	setSpeed(0);

	//move add shape to Wall methods
	getColShape()->addShape( Pos(), rect->w, rect->h );


	setMovable(false);
}

Wall::Wall( float x, float y, std::shared_ptr<Rectangle> rect )
{
	Velocity(0, 0);
	
	
	Pos()->setX( x );
	Pos()->setY( y );
	setMass(100);
	setSpeed(0);

	//move add shape to Wall methods
	getColShape()->addShape( Pos(), rect->w, rect->h );


	setMovable(false);
}

Wall::Wall( float x, float y, std::shared_ptr< Texture > text )
{
	Velocity(0, 0);
	
	setSkin( text, tWall );
	Pos()->setX(x);
	Pos()->setY(y);
	setMass(100);
	setSpeed(0);

	
	getColShape()->addShape(Pos(), text, sBox);


	setMovable(false);
}

Wall::Wall(std::shared_ptr< Vector2d > vec, std::shared_ptr< Texture > text )
{
	Velocity(0, 0);
	
	setSkin( text, tWall );
	Pos( vec );
	setMass(100);
	setSpeed(0);

	//move add shape to Wall methods
	getColShape()->addShape( Pos(), text, sBox );
	getColShape()->Update( Pos() );

	setMovable(false);
}

Wall::Wall(std::shared_ptr<Vector2d> vec, Rectangle & rect)
{
}

Wall::~Wall()
{
}

void Wall::Draw()
{
	//getSkin()->render( Pos()->getX() - std::static_pointer_cast< Rectangle >( getColShape()->getFirst() )->w / 2,
	//				   Pos()->getY() - std::static_pointer_cast< Rectangle >( getColShape()->getFirst() )->h / 2 );
	getSkin()->render( Pos() );
}

void Wall::Update(std::shared_ptr<Object> obj)
{
}

void Wall::collisionDetected(std::shared_ptr<Object> obj)
{
}
