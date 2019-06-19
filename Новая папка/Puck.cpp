#include "stdafx.h"
#include "Puck.h"


Puck::Puck() : Entity()
{
	setSkin(TextureManager::getTexture("Puck.png"), tPuck);
	Pos()->setX( ( SDL_wrapper::displayMode.w / 2 ) / 2 );
	Pos()->setY( ( SDL_wrapper::displayMode.h / 2 ) / 2 );
	setMass(10);
	colShape = std::make_shared< CollisionShape >();
	colShape->addShape( Pos(), skin, sCircle );

	setSpeed( 100 );

	
	movable = true;
}


Puck::~Puck()
{
}
void Puck::moveTo(float x1, float y1, float x2, float y2)
{
	float speed = (rand() % 20);

	float dist = distance(x1, y1, x2, y2);
	float dX = x2 - x1;
	float dY = y2 - y1;

	if (dist > speed) {

		updatePosition(x1 + speed / dist * dX, y1 + speed / dist * dY);

	}
	else
	{
		updatePosition(x2, y2);
	}

}
void Puck::Update(std::shared_ptr<Object> obj)
{
	std::cout << "Puck" << Velocity() <<std::endl;
	//updatePosition();

	//updatePosition();
	
	//Acceleration()->setX( ( -Velocity()->getX() * 0.8f) );
	//
	//Acceleration()->setY( ( -Velocity()->getY() * 0.8f ) );
	//
	//Velocity()->addX( Acceleration()->getX() * ( TimerIns::Instance()->DeltaTime() / 1000.0f ) );
	//
	//Velocity()->addY( Acceleration()->getY() * ( TimerIns::Instance()->DeltaTime() / 1000.0f ) );
	//
	////Velocity()->normalise();
	//
	//Pos()->addX( ( Velocity()->getX() * ( TimerIns::Instance()->DeltaTime() / 1000.0f) ) );
	//
	//Pos()->addY( ( Velocity()->getY() * ( TimerIns::Instance()->DeltaTime() / 1000.0f) ) );
	//
	//colShape->Update( Pos() );

	std::cout << "Puck" << std::endl;
	if ( fabs( Velocity()->getX() * Velocity()->getX() + Velocity()->getY() * Velocity()->getY()) < 0.001f)
	{
	
		Velocity( 0, 0 );
	
	}
	/*
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
	
	}*/
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


