#include "stdafx.h"
#include "Entity.h"


Entity::Entity() : Object()
{
	movable = true;
}


Entity::~Entity()
{
}

void Entity::setMoveBounds(std::shared_ptr< Vector2d > bounds)
{
	this->moveBounds = bounds;
}

void Entity::setMoveBounds(float x, float y)
{
	this->moveBounds = std::make_shared< Vector2d >( x, y );
}

void Entity::setVelocity(std::shared_ptr< Vector2d > velocity)
{
	this->velocity = velocity;
}

void Entity::setVelocity(float x, float y)
{
	this->velocity = std::make_shared< Vector2d >( x, y );
}

std::shared_ptr< Vector2d > Entity::getMoveBounds()
{
	return moveBounds;
}

std::shared_ptr< Vector2d > Entity::getVelocity()
{
	return velocity;
}

void Entity::move()
{
}

void Entity::Update(std::shared_ptr< Object > obj)
{
}

void Entity::collisionDetected(std::shared_ptr< Object > obj)
{
}
