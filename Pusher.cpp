#include "stdafx.h"
#include "Pusher.h"


Pusher::Pusher() : Entity()
{

	colShape = std::make_shared< CollisionShape >();
	//setMoveBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
	setVelocity(0, 0);
	std::cout << "PL S" << std::endl;
	setSkin(TextureManager::getTexture("Rocket.png"), tPusher);
	Pos()->setX( SCREEN_HEIGHT / 4 );
	Pos()->setY( SCREEN_HEIGHT / 2 );
	setMass(0);

	colShape->addShape( Pos(), skin, sCircle );
	std::cout << "PL S" << std::endl;

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
		std::cout << "Pusher" << std::endl;

		updatePosition();
		std::cout << Pos() << std::endl;
		colShape->Update( Pos() );
		std::cout << "Pusher" << std::endl;

		if (Pos()->getX() - getColShape()->getCircle()->getRadius() <= 0)
		{
		
			Pos()->setX( getColShape()->getCircle()->getRadius() );
		
		}

		if (Pos()->getY() - getColShape()->getCircle()->getRadius() <= 0)
		{

			Pos()->setY( getColShape()->getCircle()->getRadius() );
		
		}

		if (Pos()->getX() + getColShape()->getCircle()->getRadius() >= (SCREEN_WIDTH / 2))
		{
		
			Pos()->setX((SCREEN_WIDTH / 2) - getColShape()->getCircle()->getRadius() );
		
		}
		if (Pos()->getY() + getColShape()->getCircle()->getRadius() >= SCREEN_HEIGHT )
		{

			Pos()->setY( (SCREEN_HEIGHT) - getColShape()->getCircle()->getRadius() );
		
		}
		std::cout << "Pusher" << std::endl;
		colShape->Update( Pos() );
		std::cout << "Pusher" << std::endl;

}

void Pusher::collisionDetected(std::shared_ptr<Object> obj)
{

}

