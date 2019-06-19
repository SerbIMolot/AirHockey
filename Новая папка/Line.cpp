#include "stdafx.h"
#include "Line.h"



Line::Line(float x1, float y1, float x2, float y2, float r)
	: Shape( x1, y1 , sLine )
{
	endPoint = std::make_shared< Vector2d >( x2, y2 );
	
	setRadius( r );

}

Line::Line(std::shared_ptr<Vector2d> start, std::shared_ptr<Vector2d> end, float r)
	: Shape( start , sLine )
{

	endPoint = std::move( end );

	setRadius( r );

}

std::shared_ptr<Vector2d> Line::getEndPoint()
{
	return endPoint;
}

float Line::getRadius()
{
	return r;
}

void Line::setRadius( float r )
{
	this->r = r;
}

Line::~Line()
{
}
