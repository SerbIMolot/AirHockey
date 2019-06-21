#include "stdafx.h"
#include "Shape.h"


Shape::Shape( cShape type )
{

	pos = std::make_shared< Vector2d >( 0, 0 );
	
	this->type = type;

}

Shape::Shape( std::shared_ptr<Vector2d> vec , cShape type )
{

	pos = std::move( vec );

	this->type = type;
}

Shape::Shape(float x, float y, cShape type )
{

	pos = std::make_shared< Vector2d >( x, y );
	
	this->type = type;
}


Shape::~Shape()
{
}

void Shape::Update(std::shared_ptr<Vector2d> vec)
{
	pos = vec ;
}

void Shape::Update(float x, float y)
{
	pos->setX( x );
	pos->setY( y );
}

std::shared_ptr<Vector2d> Shape::Pos()
{
	return pos;
}

float Shape::getX()
{
	return pos->getX();
}

float Shape::getY()
{
	return pos->getY();
}

cShape Shape::getType()
{
	return type;
}


