#include "stdafx.h"
#include "Trigger.h"


Trigger::Trigger(std::shared_ptr<Vector2d> vec, int w, int h)
{

	this->pos = std::move( vec );
	rect = std::make_shared< Rectangle >( pos, w, h );

}

Trigger::Trigger(std::shared_ptr<Vector2d> vec, std::shared_ptr<Rectangle> rect)
{

	this->pos = std::move( vec );
	rect = std::move( rect );

}

Trigger::Trigger(int x, int y, int w, int h)
{

	this->pos = std::make_shared< Vector2d >( x, y );
	rect = std::make_shared< Rectangle >( pos, w, h );

}

Trigger::~Trigger()
{
}
