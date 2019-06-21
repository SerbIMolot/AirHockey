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
	setMass(20);

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
		std::cout << "Pusher" << std::endl;
		colShape->Update( Pos() );
		std::cout << "Pusher" << std::endl;

}

void Pusher::collisionDetected(std::shared_ptr<Object> obj)
{

}

