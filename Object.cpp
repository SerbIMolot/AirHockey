#include "stdafx.h"
#include "Object.h"



Object::Object()
{
	position = std::make_shared< Vector2d >(0, 0);
	previousPos = std::make_shared< Vector2d >(0, 0);
	velocity = std::make_shared< Vector2d >(0, 0);
	acceleration = std::make_shared< Vector2d >(0, 0);
	previousVel = std::make_shared< Vector2d >(0, 0);


	colShape = std::make_shared< CollisionShape >();
	rotation = 0.0f;
	active = false;
	skin = nullptr;


	type = tUndefined;

	timer = std::make_shared< Timer >();


	setMass( 2 );
}

Object::Object(float x, float y, std::shared_ptr<Texture> textr, Type type , cShape shape )
{

	position = std::make_shared< Vector2d >(x, y);
	previousPos = std::make_shared< Vector2d >(0, 0);
	velocity = std::make_shared< Vector2d >(0, 0);
	acceleration = std::make_shared< Vector2d >(0, 0);
	previousVel = std::make_shared< Vector2d >(0, 0);
	timer = std::make_shared< Timer >();


	rotation = 0.0f;
	active = true;
	setMass(2);
	
	if (textr == nullptr) {


		this->type = type;
		skin = textr;
	}
	else {

		setSkin(textr, type);
	}
}

Object::Object(std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> textr, Type type, cShape shape )
{
	position = vec;
	previousPos = std::make_shared< Vector2d >(0, 0);
	velocity = std::make_shared< Vector2d >(0, 0);
	acceleration = std::make_shared< Vector2d >(0, 0);
	previousVel = std::make_shared< Vector2d >(0, 0);


	rotation = 0.0f;
	active = true;

	timer = std::make_shared< Timer >();
	setMass(100);
	if (textr == nullptr) {

		this->type = type;
	}
	else {

		setSkin(textr, type);
	}
}

Object::~Object()
{
}

void Object::Pos(std::shared_ptr< Vector2d > vec) 
{
	this->position = vec;
}


void Object::Active(bool active)
{
	this->active = active;
}

bool Object::Active()
{
	return active;
}

void Object::updatePosition(float x, float y)
{
	prevPos(Pos());
	
	if (prevPos()->getX() != x || prevPos()->getY() != y )
	{
		if( x == -1 && y == -1 )
		{
			updateVelocity( Pos()->getX(), Pos()->getY() );
		}
		else
		{ 
			updateVelocity(x, y);
			Pos(x, y);
		}
		
	}
}

void Object::updateVelocity(float x, float y )
{
	prevVel( Velocity() );

	updateAccel( x, y );

	Velocity( )->addX( Acceleration()->getX() );
	
	Velocity( )->addY( Acceleration()->getY() );
	
	Velocity()->normalise();
}

void Object::updateAccel(float x, float y )
{

	Acceleration()->setX( ( x - prevPos()->getX() ) * (TimerIns::Instance()->DeltaTime() / 1000.0f ) );
	Acceleration()->setY( (y - prevPos()->getY() ) * (TimerIns::Instance()->DeltaTime() / 1000.0f) );

}

void Object::setSkin( std::shared_ptr<Texture> texture, Type type )
{
	this->skin = texture;
	this->type = type;

	Pos( std::make_shared < Vector2d >( position->getX() - ( skin->getWidth() / 2.0f ), position->getY() - ( skin->getHeight() / 2.0f ) ) );
	
}

std::shared_ptr<Texture> Object::getSkin()
{
	return skin;
}


Type Object::getType()
{
	return type;
}

void Object::setType(Type type) {
	this->type = type;
}


void Object::Rotation(float r) {
	rotation = r;
	if (rotation > 360.0f) {
		rotation -= 360.0f;
	}
	if (rotation < 0.0f) {
		rotation += 360.0f;
	}
}

float Object::Rotation(SPACE space) {
	if (space == screen ) {
		return rotation;
	}
	return  rotation;
}


void Object::Update( std::shared_ptr< Object > obj ) {
	
	
}



std::shared_ptr<Vector2d> Object::prevPos()
{
	return previousPos;
}

void Object::prevPos( std::shared_ptr<Vector2d> vec )
{
	previousPos = std::move(vec);
}

void Object::prevPos(int x, int y)
{
	previousPos->setX( x );
	previousPos->setY( y );
}

std::shared_ptr<Vector2d> Object::prevVel()
{
	return previousVel;
}

void Object::prevVel(std::shared_ptr<Vector2d> vec)
{
	previousVel = std::move(vec);
}

void Object::prevVel (int x, int y)
{
	previousVel->setX(x);
	previousVel->setY(y);
}


std::shared_ptr<Vector2d> Object::Pos()
{
	return position;
}



void Object::Pos(int x, int y)
{
	position->setX( static_cast< float >( x ) );
	position->setY( static_cast< float >( x ) );
}

void Object::Pos(float x, float y)
{
	position->setX( x );
	position->setY( y );
}

void Object::setMass(float x)
{
	mass = x;
}

void Object::setMass(int x)
{
	mass = static_cast< float >( x );
}

float Object::getMass()
{
	return mass;
}

std::shared_ptr<Vector2d> Object::Velocity()
{
	return velocity;
}

void Object::Velocity(std::shared_ptr<Vector2d> vec)
{
	velocity = std::move(vec);
}

void Object::Velocity(float x, float y)
{
	velocity->setX( x );
	velocity->setY( y );
}

std::shared_ptr<Vector2d> Object::Acceleration()
{
	return acceleration;
}

std::shared_ptr< CollisionShape > Object::getColShape()
{
	return colShape;
}

bool Object::isMovable()
{
	return movable;
}

float Object::getSpeed()
{
	return speed;
}

void Object::Acceleration(std::shared_ptr<Vector2d> vec)
{
	acceleration = std::move(vec);
}

void Object::Acceleration(float x, float y)
{
	acceleration->setX( x );
	acceleration->setY( y );
}

void Object::setMovable(bool mov)
{
	movable = mov;
}

void Object::setSpeed(float s)
{
	speed = s;
}

void Object::moveTo(int x, int y)
{

}

bool Object::outOfBounds()
{
	return false;
}
