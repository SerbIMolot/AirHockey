#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle()
	: Shape( sBox ) 
{

	w = 0;
	h = 0;

}

Rectangle::Rectangle(int x, int y, int w, int h) 
	: Shape( static_cast<float>(x), static_cast<float>(y), sBox)
{
	this->x = static_cast<float>(x);
	this->x = static_cast<float>(y);
	this->w = static_cast<float>(w);
	this->h = static_cast<float>(h);

}

Rectangle::Rectangle(float x, float y, float w, float h) 
	: Shape( x, y, sBox )
{

	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

}

Rectangle::Rectangle(std::shared_ptr<Vector2d> vec, float w, float h)
	: Shape( vec, sBox )
{
	this->x = vec->getX();
	this->y = vec->getY();
	this->w = w;
	this->h = h;
}

Rectangle::Rectangle(std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> texture) 
	: Shape( vec, sBox )
{
	this->x = vec->getX();
	this->y = vec->getY();
	if (texture == nullptr) {
		w = 0;
		h = 0;
	}
	else {
		w = static_cast<float>(texture->getWidth());
		h = static_cast<float>(texture->getHeight());
	}

}

Rectangle::~Rectangle() { }


float Rectangle::topSide()
{
	return getY();
}

float Rectangle::BottomSide()
{
	return getY() + h;
}

float Rectangle::LeftSide()
{
	return getX();
}

float Rectangle::RightSide()
{
	return getX() + w;
}

SDL_Rect Rectangle::convertToSDLRect()
{
	SDL_Rect buf = { static_cast< int >( getX() ), static_cast<  int >( getY() ), static_cast< int >( w ), static_cast< int >( h ) };
	return buf;

}

