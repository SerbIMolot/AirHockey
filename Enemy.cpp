#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
	: Entity()
{

	setVelocity(0, 0);
	
	setSkin(TextureManager::getTexture("Rocket.png"), tPusher);
	
	Pos()->setX( SCREEN_WIDTH / 2 + SCREEN_WIDTH / 3 );
	Pos()->setY( SCREEN_HEIGHT / 2 );

	getColShape()->addShape( Pos(), getSkin(), sCircle );

	setMass(20);

	targetPos = std::make_shared< Vector2d >();
	lastHit.start();
	
}


Enemy::~Enemy()
{
}

bool Enemy::puckInCorner()
{
	if ( puck->Pos()->getX() > SCREEN_WIDTH / 2 - 1 )
	{
		return true;
	}
	return false;
}

void Enemy::moveTo(float x1, float y1, float x2, float y2)
{
	float speed = static_cast< float >(rand() % 15);

	float dist = distance( x1, y1 , x2, y2 );
	float dX = x2 - x1;
	float dY = y2 - y1;

	if (dist > speed) {

		updatePosition( x1 + speed / dist * dX, y1 + speed / dist * dY );

	}
	else
	{

		updatePosition( x2, y2 );

	}

}

void Enemy::Attack()
{

	moveTo( Pos()->getX(), Pos()->getY(), puck->Pos()->getX(), puck->Pos()->getY() );

}

void Enemy::defence()
{	

	moveTo( Pos()->getX() , Pos()->getY(), SCREEN_WIDTH - 150 , puck->Pos()->getY() );

}

void Enemy::doNothing()
{

	moveTo( Pos()->getX(), Pos()->getY(), SCREEN_WIDTH / 2 + SCREEN_WIDTH / 3,  SCREEN_HEIGHT / 2 );

}

void Enemy::makeDecision()
{
	if( puckInCorner() && puck->Velocity()->getX() == 0 )
	{
		Attack();
		return;
	}

	if ( puck->Velocity()->getX() > 0 ) 
	{

		
		if( Pos()->getX() < puck->Pos()->getX() )
		{
			doNothing();
			return;
		}
		if ( puckInCorner() && lastHit.getTicks() > 800 )
		{

			Attack();

		}
		else
		{
			defence();
		}

	}
	else
	{
		defence();
	}


}
void Enemy::Update( std::shared_ptr< Object > obj1 )
{
	
	makeDecision();
	
	if (Pos()->getX() - getColShape()->getCircle()->getRadius() <= SCREEN_WIDTH / 2)
	{

		Pos()->setX((SCREEN_WIDTH / 2) + getColShape()->getCircle()->getRadius());

	}
	if (Pos()->getY() - getColShape()->getCircle()->getRadius() <= 15)
	{

		Pos()->setY(getColShape()->getCircle()->getRadius() + 15);

	}

	if (Pos()->getX() + getColShape()->getCircle()->getRadius() >= SCREEN_WIDTH - 15)
	{
		
		Pos()->setX( (SCREEN_WIDTH) - getColShape()->getCircle()->getRadius() - 15);

	}
	if (Pos()->getY() + getColShape()->getCircle()->getRadius() >= SCREEN_HEIGHT - 15)
	{

		Pos()->setY((SCREEN_HEIGHT) - getColShape()->getCircle()->getRadius() - 15);

	}

	
	getColShape()->Update( Pos() );

}

void Enemy::move()
{
}
void Enemy::Draw()
{

	getSkin()->render( Pos()->getX() - getColShape()->getCircle()->getRadius(), Pos()->getY() - getColShape()->getCircle()->getRadius() );

}

void Enemy::setPuck(std::shared_ptr<Puck> puck)
{
	this->puck = puck;
}

void Enemy::collisionDetected(std::shared_ptr<Object> obj)
{
	if( obj->getType() == tPuck )
	{
		lastHit.stop();
		lastHit.start();
	}
}
