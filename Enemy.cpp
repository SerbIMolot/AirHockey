#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
	: Entity()
{
	setMoveBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
	setVelocity(0, 0);
	
	setSkin(TextureManager::getTexture("Rocket.png"), tPusher);
	
	Pos()->setX( SDL_wrapper::displayMode.w / 4 + SDL_wrapper::displayMode.w / 6 );
	Pos()->setY( SDL_wrapper::displayMode.h / 4 );

	getColShape()->addShape( Pos(), getSkin(), sCircle );
	std::cout << Pos() << std::endl;
	setMass(100);
	maxMovementSpeed = 300;
	eSpeed = 200.0f;
	targetPos = std::make_shared< Vector2d >();
	lastHit.start();
}


Enemy::~Enemy()
{
}

bool Enemy::puckInCorner()
{
	if ( puck->Pos()->getX() > SDL_wrapper::displayMode.w / 4 + std::static_pointer_cast< Circle >( puck->getShape() )->getRadius() )
	{
		return true;
	}
	return false;
}

void Enemy::moveTo(float x1, float y1, float x2, float y2)
{
	float speed = (rand() % 20);

	float dist = distance( x1, y1 , x2, y2 );
	float dX = x2 - x1;
	float dY = y2 - y1;

	if (dist > speed) {

		updatePosition( x1 + speed / dist * dX, y1 + speed / dist * dY );

	}

}

void Enemy::Attack()
{

	moveTo(Pos()->getX(), Pos()->getY(), puck->Pos()->getX(), puck->Pos()->getY() );

}

void Enemy::defence()
{	
	std::uniform_real_distribution< float > offsetEn(-1, 1);
	float offset = offsetEn( generator );

	moveTo( Pos()->getX() , Pos()->getY(), SDL_wrapper::displayMode.w / 4 + SDL_wrapper::displayMode.w / 6, puck->Pos()->getY() + offset );
	
	
}
void Enemy::makeDecision()
{
	if ( puckInCorner() && puck->Pos()->getX() < Pos()->getX() )
	{
		Attack();
	}
	else
	{
		defence();
	}
	
}
void Enemy::Update( std::shared_ptr< Object > obj1 )
{
	
	makeDecision();
	
	if (Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() <= SDL_wrapper::displayMode.w / 4)
	{

		Pos()->setX((SDL_wrapper::displayMode.w / 4) + std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());

	}
	if (Pos()->getY() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() <= 0)
	{

		Pos()->setY(std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());

	}

	if (Pos()->getX() + std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() >= SDL_wrapper::displayMode.w / 2)
	{
		
		Pos()->setX((SDL_wrapper::displayMode.w / 2) - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());

	}
	if (Pos()->getY() + std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() >= SDL_wrapper::displayMode.h / 2)
	{

		Pos()->setY((SDL_wrapper::displayMode.h / 2) - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());

	}

	updatePosition();
	getShape()->Update( Pos() );

}

void Enemy::move()
{
}
void Enemy::Draw()
{
	std::cout << "EnemyDrawPos = " << Pos()->getX() << std::endl;
	std::cout << "Enemy RADIUS = " << std::static_pointer_cast<Circle>(getColShape()->getShapes().front())->getRadius() << std::endl;
	getSkin()->render( Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius(), Pos()->getY() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() );
}

void Enemy::setPuck(std::shared_ptr<Puck> puck)
{
	this->puck = puck;
}

void Enemy::collisionDetected(std::shared_ptr<Object> obj)
{
}
