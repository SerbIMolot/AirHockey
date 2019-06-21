#include "stdafx.h"
#include "Pusher.h"


Pusher::Pusher() : Entity()
{

	colShape = std::make_shared< CollisionShape >();

	setVelocity(0, 0);

	setSkin(TextureManager::getTexture("Rocket.png"), tPusher);
	Pos()->setX( SCREEN_HEIGHT / 4 );
	Pos()->setY( SCREEN_HEIGHT / 2 );
	setMass(20);

	colShape->addShape( Pos(), skin, sCircle );


	movable = true;
}


Pusher::~Pusher()
{
}


void Pusher::Draw()
{
	getSkin()->render( Pos()->getX() - getColShape()->getCircle()->getRadius(), Pos()->getY() - getColShape()->getCircle()->getRadius() );

}

void Pusher::move()
{
}

void Pusher::Update(std::shared_ptr<Object> obj)
{

		updatePosition();

		colShape->Update( Pos() );


		if (Pos()->getX() - getColShape()->getCircle()->getRadius() <= 15 )
		{
		
			Pos()->setX( getColShape()->getCircle()->getRadius() + 15 );
		
		}

		if (Pos()->getY() - getColShape()->getCircle()->getRadius() <= 15)
		{

			Pos()->setY( getColShape()->getCircle()->getRadius() + 15 );
		
		}

		if (Pos()->getX() + getColShape()->getCircle()->getRadius() >= (SCREEN_WIDTH / 2))
		{
		
			Pos()->setX((SCREEN_WIDTH / 2) - getColShape()->getCircle()->getRadius() );
		
		}
		if (Pos()->getY() + getColShape()->getCircle()->getRadius() >= SCREEN_HEIGHT-15 )
		{

			Pos()->setY( (SCREEN_HEIGHT) - getColShape()->getCircle()->getRadius() - 15 );
		
		}

		colShape->Update( Pos() );


}

void Pusher::collisionDetected(std::shared_ptr<Object> obj)
{

}

