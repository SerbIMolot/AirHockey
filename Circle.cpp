#include "Circle.h"
#include "stdafx.h"

Circle::Circle(std::shared_ptr<Vector2d> vec, std::shared_ptr<Texture> textr )
	: Shape( vec, sCircle )
{

	setRadius( textr->getHeight() / 2 );

}

Circle::Circle(int x, int y, std::shared_ptr<Texture> textr)
	: Shape( x, y, sCircle )
{

	setRadius( textr->getHeight() / 2 );

}

Circle::Circle(int x, int y, int radius)
	: Shape( x, y, sCircle )
{

	setRadius( radius );

}

Circle::Circle(std::shared_ptr<Vector2d> vec, int radius)
	: Shape( vec, sCircle )
{

	setRadius( radius );

}

void Circle::setVec(std::shared_ptr<Vector2d> vec)
{
	Update( vec );
}

std::shared_ptr<Vector2d> Circle::getVec()
{
	return Pos();
}

void Circle::setRadius(int rad)
{
	radius = rad;
}

int Circle::getRadius()
{
	return radius;
}
