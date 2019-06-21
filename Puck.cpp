#include "stdafx.h"
#include "Puck.h"


Puck::Puck() : Entity()
{
	setSkin(TextureManager::getTexture("Puck.png"), tPuck);
	Pos()->setX( ( SCREEN_WIDTH ) / 2 );
	Pos()->setY( ( SCREEN_HEIGHT ) / 2 );
	setMass(5);
	colShape = std::make_shared< CollisionShape >();
	colShape->addShape( Pos(), skin, sCircle );

	timer->start();
	
	movable = true;
}


Puck::~Puck()
{
}

void Puck::Update(std::shared_ptr<Object> obj)
{

	Acceleration()->setX( ( -Velocity()->getX() * 0.99f) );
	
	Acceleration()->setY( ( -Velocity()->getY() * 0.99f ) );
	
	Velocity()->addX( Acceleration()->getX() * ( TimerIns::Instance()->DeltaTime() / 1000.0f ) );
	
	Velocity()->addY( Acceleration()->getY() * (TimerIns::Instance()->DeltaTime() / 1000.0f) );

	Pos()->addX( ( Velocity()->getX() * (TimerIns::Instance()->DeltaTime() / 1000.0f) ) * 300 );

	Pos()->addY( ( Velocity()->getY() * (TimerIns::Instance()->DeltaTime() / 1000.0f) ) * 300 );
	
	colShape->Update( Pos() );

	if (Pos()->getX() - std::static_pointer_cast<Circle>(getColShape()->getShapes().front())->getRadius() <= 15)
	{

		Pos()->setX( getColShape()->getCircle()->getRadius() + 15 );
		
		Velocity()->setX(-Velocity()->getX());

	}

	if (Pos()->getY() - getColShape()->getCircle()->getRadius() <= 15)
	{

		Pos()->setY(getColShape()->getCircle()->getRadius() + 15 );
		
		Velocity()->setY(-Velocity()->getY());
	
	}

	if (Pos()->getX() + getColShape()->getCircle()->getRadius() >= SCREEN_WIDTH - 15 )
	{
		
		Pos()->setX((SCREEN_WIDTH) - getColShape()->getCircle()->getRadius() - 15 );
	
		Velocity()->setX( -Velocity()->getX() );
	
	}

	if (Pos()->getY() + getColShape()->getCircle()->getRadius() >= SCREEN_HEIGHT - 15)
	{
	
		Pos()->setY( (SCREEN_HEIGHT) - getColShape()->getCircle()->getRadius() - 15 );
	
		Velocity()->setY( -Velocity()->getY() );
	
	}

	colShape->Update( Pos() );

}

void Puck::move()
{
}

void Puck::Draw()
{
	getSkin()->render( Pos()->getX() - getColShape()->getCircle()->getRadius(), Pos()->getY() - getColShape()->getCircle()->getRadius() );
}

void Puck::collisionDetected( std::shared_ptr<Object> obj )
{
	if( obj->getType() == tPusher && timer->getTicks() > 200 )
	{
		
		SoundManager::getSound("puck_hit.wav")->play();

		timer->stop();
		timer->start();
	}
		
}


