#include "stdafx.h"
#include "Pusher.h"


Pusher::Pusher() : Entity()
{

	colShape = std::make_shared< CollisionShape >();
	setMoveBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
	setVelocity(0, 0);
	std::cout << "PL S" << std::endl;
	setSkin(TextureManager::getTexture("Rocket.png"), tPusher);
	Pos()->setX( SDL_wrapper::displayMode.w / 8 );
	Pos()->setY( SDL_wrapper::displayMode.h / 4 );
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
	getSkin()->render( Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius(), Pos()->getY() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() );

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

		if (Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() <= 0)
		{
		
			Pos()->setX(std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());
		
		}

		if (Pos()->getY() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() <= 0)
		{

			Pos()->setY(std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());
		
		}

		if (Pos()->getX() + std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() >= (SDL_wrapper::displayMode.w / 4))
		{
		
			Pos()->setX((SDL_wrapper::displayMode.w / 4) - std::static_pointer_cast<Circle>(getShape())->getRadius());
		
		}
		if (Pos()->getY() + std::static_pointer_cast<Circle>(getShape())->getRadius() >= SDL_wrapper::displayMode.h / 2)
		{

			Pos()->setY((SDL_wrapper::displayMode.h / 2) - std::static_pointer_cast<Circle>(getShape())->getRadius());
		
		}
		std::cout << "Pusher" << std::endl;
		colShape->Update( Pos() );
		std::cout << "Pusher" << std::endl;

}

void Pusher::collisionDetected(std::shared_ptr<Object> obj)
{

}

