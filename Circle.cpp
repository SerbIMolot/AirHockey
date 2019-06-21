
#include "stdafx.h"

Circle::Circle(std::shared_ptr<Vector2d> vec, std::shared_ptr<Texture> textr )
	: Shape( vec, sCircle )
{

	setRadius( textr->getHeight() / 2 );

}

Circle::Circle(int x, int y, std::shared_ptr<Texture> textr)
	: Shape( static_cast<float>( x ), static_cast<float>( y ), sCircle )
{

	setRadius( textr->getHeight() / 2 );

}

Circle::Circle(float x, float y, float radius)
	: Shape( x, y, sCircle)
{

		setRadius(radius);
}

Circle::Circle(int x, int y, int radius)
	: Shape( static_cast< float >( x ), static_cast< float >( y ), sCircle )
{

	setRadius( radius );

}

Circle::Circle(std::shared_ptr<Vector2d> vec, int radius)
	: Shape( vec, sCircle )
{

	setRadius( radius );

}

float Circle::upperCircle( float x )
{
	return Pos()->getY() - sqrtf( ( getRadius() * getRadius() ) - ( ( x - Pos()->getX() ) * ( x - Pos()->getX() ) ) );
}

double Circle::lowerCircle( float x )
{
	return Pos()->getY() + sqrtf( ( getRadius() * getRadius() ) - ( ( x - Pos()->getX() ) * (x - Pos()->getX() ) ) );
}

void Circle::setVec(std::shared_ptr<Vector2d> vec)
{
	Update( vec );
}

std::shared_ptr<Vector2d> Circle::getVec()
{
	return Pos();
}

void Circle::setRadius( float rad )
{
	radius = rad;
}

void Circle::setRadius( int rad )
{
	radius = static_cast< float >( rad );
}

float Circle::getRadius()
{
	return radius;
}
