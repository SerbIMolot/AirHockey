#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle()
	: Shape( sBox ) 
{

	w = 0;
	h = 0;

}

Rectangle::Rectangle(int x, int y, int w, int h) 
	: Shape(x, y, sBox)
{

	this->w = static_cast<float>(w);
	this->h = static_cast<float>(h);

}

Rectangle::Rectangle(float x, float y, float w, float h) 
	: Shape( x, y, sBox )
{

	this->w = w;
	this->h = h;

}

Rectangle::Rectangle(std::shared_ptr<Vector2d> vec, float w, float h)
	: Shape( vec, sBox )
{
	this->w = w;
	this->h = h;
}

Rectangle::Rectangle(std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> texture) 
	: Shape( vec, sBox )
{

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
	return y;
}

float Rectangle::BottomSide()
{
	return y + h;
}

float Rectangle::LeftSide()
{
	return x;
}

float Rectangle::RightSide()
{
	return x + w;
}

