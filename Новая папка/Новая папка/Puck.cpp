#include "stdafx.h"
#include "Puck.h"


Puck::Puck() : Entity()
{
	setSkin(TextureManager::getTexture("Puck.png"), tPuck);
	Pos()->setX( ( SDL_wrapper::displayMode.w / 2 ) / 2 );
	Pos()->setY( ( SDL_wrapper::displayMode.h / 2 ) / 2 );
	setMass(12);
	colShape = std::make_shared< CollisionShape >();
	colShape->addShape( Pos(), skin, sCircle );

	
	movable = true;
}


Puck::~Puck()
{
}

void Puck::Update(std::shared_ptr<Object> obj)
{
	std::cout << "Puck" << std::endl;
	
	Acceleration()->setX( ( -Velocity()->getX() * 0.97f) );
	
	Acceleration()->setY( ( -Velocity()->getY() * 0.97f ) );
	
	Velocity()->addX( Acceleration()->getX() * ( TimerIns::Instance()->DeltaTime() / 1000.0f ) );
	
	Velocity()->addY( Acceleration()->getY() * (TimerIns::Instance()->DeltaTime() / 1000.0f) );

	Pos()->addX( ( Velocity()->getX() * (TimerIns::Instance()->DeltaTime() / 1000.0f) ) * 300 );

	Pos()->addY( ( Velocity()->getY() * (TimerIns::Instance()->DeltaTime() / 1000.0f) ) * 300 );
	
	colShape->Update( Pos() );

	std::cout << "Puck" << std::endl;
	if ( fabs( Velocity()->getX() * Velocity()->getX() + Velocity()->getY() * Velocity()->getY()) < 0.001f)
	{
	
		Velocity( 0, 0 );
	
	}

	if (Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front())->getRadius() <= 0)
	{

		Pos()->setX( std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() );
		
		Velocity()->setX(-Velocity()->getX());

	}

	if (Pos()->getY() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() <= 0)
	{

		Pos()->setY(std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius());
		
		Velocity()->setY(-Velocity()->getY());
	
	}

	if (Pos()->getX() + std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() >= SDL_wrapper::displayMode.w / 2)
	{
		
		Pos()->setX((SDL_wrapper::displayMode.w / 2) - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() );
	
		Velocity()->setX( -Velocity()->getX() );
	
	}

	if (Pos()->getY() + std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() >= SDL_wrapper::displayMode.h / 2)
	{
	
		Pos()->setY( (SDL_wrapper::displayMode.h / 2) - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() );
	
		Velocity()->setY( -Velocity()->getY() );
	
	}
	std::cout << "Puck" << std::endl;
	colShape->Update( Pos() );
	std::cout << "Puck" << std::endl;
}

void Puck::move()
{
}

void Puck::Draw()
{
	getSkin()->render( Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius(), Pos()->getY() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front() )->getRadius() );
}

void Puck::collisionDetected( std::shared_ptr<Object> obj )
{
		
}


