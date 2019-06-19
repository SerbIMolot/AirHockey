#include "stdafx.h"
#include "Collision.h"


std::vector< std::shared_ptr< Object > > Collision::Objects = std::vector< std::shared_ptr< Object > >();

Collision::Collision()
{
	numSimulationUpdates = 4;

	tSimulationElapsTime = ( TimerIns::Instance()->ElapsTicks() / 1000.0f) / static_cast< float >( numSimulationUpdates );

	numMaxSimSteps = 15;
}


Collision::~Collision()
{
}

void Collision::addObject( std::shared_ptr< Object > obj )
{

	Collision::Objects.push_back( std::move( obj ) );

}

void Collision::addCollidedObject(  std::shared_ptr< Object > obj1, std::shared_ptr< Object > obj2 )
{
	if ( collidedObjects.count( obj1 ) == 0 && collidedObjects.count( obj2 ) == 0
		&& obj1->getType() != tMouse && obj2->getType() != tMouse )
	{
		collidedObjects[obj1] = obj2;

		obj1->collisionDetected( obj2 );

		obj2->collisionDetected( obj1 );

	}
	
}

void Collision::Update()
{
	tSimulationElapsTime = ( TimerIns::Instance()->DeltaTime() / static_cast< float >( numSimulationUpdates )  / 1000.0f );
	// main loop for simulation
	for( int i = 0; i < numSimulationUpdates; i++ )
	{
		// Update how much time each object will be in simulation
		for( auto obj : Objects )
		{
			obj->setSimTimeRem( tSimulationElapsTime );
			obj->getColShape()->Update( obj->Pos() );
		}

		for( int j = 0; j < numMaxSimSteps; j++ )
		{
			//Update all objects pos
			for( auto obj : Objects )
			{
				if ( obj->getSimTimeRem() > 0.0f && obj->getType() != tPusher )
				{
					
					//std::cout << "SIM TIME = " << obj->getSimTimeRem() << std::endl;
					obj->prevPos( obj->Pos() );
					
					obj->Acceleration()->setX( ( -obj->Velocity()->getX() * 0.8f) );
					
					obj->Acceleration()->setY( ( -obj->Velocity()->getY() * 0.8f ) );
						
					obj->Velocity()->addX( obj->Acceleration()->getX() * obj->getSimTimeRem() * obj->getSpeed());
						
					obj->Velocity()->addY( obj->Acceleration()->getY() * obj->getSimTimeRem() * obj->getSpeed());
					
				//	obj->Velocity()->normalise();
					//obj->Velocity( *obj->Velocity() * obj->getSpeed() * obj->getSimTimeRem() );
					
					obj->Pos()->addX( ( obj->Velocity()->getX() * obj->getSimTimeRem() ) );
					
					obj->Pos()->addY( ( obj->Velocity()->getY() * obj->getSimTimeRem() ) );
					
					if ( fabs( obj->Velocity()->getX() * obj->Velocity()->getX() + obj->Velocity()->getY() * obj->Velocity()->getY() ) < 0.001f)
					{
					
						obj->Velocity(0, 0);
					
					}
					// WRITE UPDATE
				}
			}

			for (auto obj1 : Objects)
			{

				for (auto obj2 : Objects)
				{

					if (obj1 == obj2)
					{
						continue;
					}

					if (collisionCheck(obj1, obj2))
					{
						std::cout << "COLLISIOM" << std::endl;
						addCollidedObject(obj1, obj2);


					}

				}

			}

			staticColisionRes();

		

			
			dynamicColisionRes();
	
		}

	
	}

	//staticColisionRes();
	//dynamicColisionRes();

	for (auto obj1 : Objects)
	{
		obj1->getShape()->Update( obj1->Pos() );
	}

	collidedObjects.clear();
}

bool Collision::collisionCheck( std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2 )
{

	for( auto sh1 : obj1->getColShape()->getShapes() )
	{ 
		for( auto sh2 : obj2->getColShape()->getShapes() )
		{ 
			
			if ( sh1->getType() == sBox && sh2->getType() == sBox )
			{

				return RectCollisionCheck( std::static_pointer_cast< Rectangle >( sh1 ), std::static_pointer_cast< Rectangle >( sh2 ) );
			
			}

			if ( sh1->getType() == sCircle && sh2->getType() == sCircle )
			{

				return circleCollisionCheck( std::static_pointer_cast< Circle >( sh1 ), std::static_pointer_cast< Circle >( sh2 ) );
			
			}

			if ( sh1->getType() == sCircle && sh2->getType() == sBox )
			{

				return circRectCollisionCheck( std::static_pointer_cast< Circle >( sh1 ), std::static_pointer_cast< Rectangle >( sh2 ) );
			
			}
			
			if ( sh1->getType() == sBox && sh2->getType() == sCircle )
			{

				return circRectCollisionCheck( std::static_pointer_cast< Circle >( sh1 ), std::static_pointer_cast< Rectangle >( sh2 ) );
	
			}
		
			/*
			if ( obj1Shape.getType() == sBox && obj2Shape.getType() == sBox )
			{

				return RectCollisionCheck( std::static_pointer_cast< Rectangle >( obj1->getShape() ), std::static_pointer_cast< Rectangle >( obj2->getShape() ) );
			
			}

			if (obj1Shape.getType() == sCircle && obj2Shape.getType() == sCircle )
			{

				return circleCollisionCheck( std::static_pointer_cast< Circle >( obj1->getShape() ), std::static_pointer_cast< Circle >( obj2->getShape() ) );
			
			}

			if ( obj1Shape.getType() == sCircle && obj2Shape.getType() == sBox )
			{

				return circRectCollisionCheck( std::static_pointer_cast< Circle >( obj1->getShape() ), std::static_pointer_cast< Rectangle >( obj2->getShape() ) );
			
			}
			
			if ( obj1Shape.getType() == sBox && obj2Shape.getType() == sCircle )
			{

				return circRectCollisionCheck( std::static_pointer_cast< Circle >( obj2->getShape() ), std::static_pointer_cast< Rectangle >( obj1->getShape() ) );
	
			}
			*/
		}

	}

	return false;

}

bool Collision::circleCollisionCheck(std::shared_ptr<Circle> circ1, std::shared_ptr<Circle> circ2)
{
	float totalDistanceSquared = circ1->getRadius() + circ2->getRadius();

	totalDistanceSquared = totalDistanceSquared * totalDistanceSquared;

	if (fabs(distanceSquared(circ1->getVec(), circ2->getVec())) <= totalDistanceSquared)
	{
		return true;
	}

	return false;
}

bool Collision::RectCollisionCheck(std::shared_ptr<Rectangle> rect, std::shared_ptr<Rectangle> rect2)
{
	if (rect->LeftSide() >= rect2->RightSide())
	{
		return false;

	}

	if (rect->RightSide() <= rect2->RightSide())
	{

		return false;

	}

	if (rect->topSide() >= rect2->BottomSide())
	{

		return false;

	}

	if (rect->BottomSide() <= rect2->topSide())
	{

		return false;

	}

	return true;

}

bool Collision::circRectCollisionCheck(std::shared_ptr<Circle> circ, std::shared_ptr<Rectangle> rect)
{
	Vector2d vec;

	if ( circ->getX() < rect->LeftSide() )
	{
		vec.setX( rect->LeftSide());

	}
	else if (circ->getX() > rect->RightSide())
	{
		vec.setX(rect->RightSide());
	}
	if (circ->getX() < rect->topSide())
	{
		vec.setY(rect->topSide());

	}
	else if (circ->getX() > rect->BottomSide())
	{
		vec.setY(rect->BottomSide());

	}

	if (vec.length() <= circ->getRadius())
	{
		return true;
	}

	return false;

}

bool Collision::pointCircleCollision( std::shared_ptr< Vector2d > vec, std::shared_ptr< Circle > circ)
{
	if ( distance( vec, circ->getVec() ) < circ->getRadius() )
	{

		return true;

	}

	return false;
}

bool Collision::lineCircleCollision(std::shared_ptr<Line> line, std::shared_ptr<Circle> circ)
{
	Vector2d line1 = Vector2d( *line->Pos() - *line->getEndPoint() );
	Vector2d line2 = Vector2d( *circ->Pos() - *line->Pos() );


	float lineLenght = line1.lengthSqr();

	float t = std::max( 0, (int)std::min( lineLenght, dotProduct( line1, line2 ) ) ) / lineLenght;

	std::shared_ptr< Vector2d > closestPoint = std::make_shared< Vector2d >( line->getX() + t * line1.getX(), line->getY() * line1.getY() );

	if ( distance( closestPoint, circ->getVec() ) <= ( circ->getRadius() + line->getRadius() ) )
	{
		return true;
	}

	return false;
}

void Collision::staticColisionRes()
{
	float overlapCoef = 0.5f;
	float pDistance = 0;
	float overlap = 0;

	for ( auto obj : collidedObjects )
	{ 
		if ( obj.first->isMovable() == false || obj.second->isMovable() == false)
		{
			overlapCoef = 1.0f;
		}
		if ( obj.first->getColShape()->getFirst()->getType() == sCircle, obj.second->getColShape()->getFirst()->getType() == sCircle )
		{ 
			pDistance = distance( obj.first->Pos(), obj.second->Pos() );
			overlap = overlapCoef * (pDistance - std::static_pointer_cast< Circle >( obj.first->getColShape()->getFirst() )->getRadius() - std::static_pointer_cast< Circle >( obj.second->getColShape()->getFirst() )->getRadius() );
		}

		if ( obj.first->getColShape()->getFirst()->getType() == sLine, obj.second->getColShape()->getFirst()->getType() == sCircle)
		{
				
		}
		//obj.first.get->getColShape()->getFirst()->getRadius();
		if ( obj.first->isMovable() == true )
		{ 
			obj.first->Pos()->addX( -( overlap * ( obj.first->Pos()->getX() - obj.second->Pos()->getX() ) / pDistance ) );
			obj.first->Pos()->addY( -( overlap * ( obj.first->Pos()->getY() - obj.second->Pos()->getY() ) / pDistance ) );
		}
		else
		{
		//	obj.second->Pos()->addX( -( overlap * ( obj.first->Pos()->getX() - obj.second->Pos()->getX() ) / pDistance ) );
		//	obj.second->Pos()->addY( -( overlap * ( obj.first->Pos()->getY() - obj.second->Pos()->getY() ) / pDistance ) );
		}

		if ( obj.second->isMovable() == true )
		{ 
			obj.second->Pos()->addX( overlap * ( obj.first->Pos()->getX() - obj.second->Pos()->getX() ) / pDistance );
			obj.second->Pos()->addY( overlap * ( obj.first->Pos()->getY() - obj.second->Pos()->getY() ) / pDistance );
		}
		else
		{
			//obj.first->Pos()->addX( (overlap * (obj.first->Pos()->getX() - obj.second->Pos()->getX()) / pDistance) );
		//	obj.first->Pos()->addY( (overlap * (obj.first->Pos()->getY() - obj.second->Pos()->getY()) / pDistance) );

		}

		obj.second->getColShape()->Update( obj.second->Pos() );
		obj.first->getColShape()->Update( obj.first->Pos() );
	

		float numIntendedSpeed1 = obj.first->Pos()->length();
		float numIntendedDistance1 = numIntendedSpeed1 * obj.first->getSimTimeRem();
		float numActualDistance1 = distance( obj.first->Pos(), obj.first->prevPos() );
		float numActualTime1 = numActualDistance1 / numIntendedSpeed1;

		obj.first->setSimTimeRem( obj.first->getSimTimeRem() - numActualTime1 );

		float numIntendedSpeed2 = obj.second->Pos()->length();
		float numIntendedDistance2 = numIntendedSpeed2 * obj.second->getSimTimeRem();
		float numActualDistance2 = distance( obj.second->Pos(), obj.second->prevPos() );
		float numActualTime2 = numActualDistance2 / numIntendedSpeed2;

		obj.second->setSimTimeRem( obj.second->getSimTimeRem() - numActualTime2 );
	}

	

}

void Collision::dynamicColisionRes()
{

	for (auto obj : collidedObjects)
	{
		float fDistance = distance( obj.first->Pos(), obj.second->Pos() );

		float nx = (obj.second->Pos()->getX() - obj.first->Pos()->getX()) / fDistance;
		float ny = (obj.second->Pos()->getY() - obj.first->Pos()->getY()) / fDistance;

		// Tangent
		float tx = -ny;
		float ty = nx;

		// Dot Product Tangent
		float dpTan1 = dotProduct(obj.first->Velocity()->getX(), obj.first->Velocity()->getY(), tx, ty);
		float dpTan2 = dotProduct(obj.second->Velocity()->getX(), obj.second->Velocity()->getY(), tx, ty);

		// Dot Product Normal
		float dpNorm1 = dotProduct(obj.first->Velocity()->getX(), obj.first->Velocity()->getY(), nx, ny);
		float dpNorm2 = dotProduct(obj.second->Velocity()->getX(), obj.second->Velocity()->getY(), nx, ny);

		// Conservation of momentum in 1D
		float m1 = 1.0f * (dpNorm1 * (obj.first->getMass() - obj.second->getMass()) + 2.0f * obj.second->getMass() * dpNorm2) / (obj.first->getMass() + obj.second->getMass());
		float m2 = 1.0f * (dpNorm2 * (obj.second->getMass() - obj.first->getMass()) + 2.0f * obj.first->getMass() * dpNorm1) / (obj.first->getMass() + obj.second->getMass());

		// Update velocities
		if (obj.first->isMovable() == true)
		{
			obj.first->Velocity()->setX(tx * dpTan1 + nx * m1);
			obj.first->Velocity()->setY(ty * dpTan1 + ny * m1);
		}
		else
		{
			//obj.second->Velocity()->setX( -( obj.second->Velocity()->getX() ) * tx * dpTan1 + nx * m1 );
			
			//obj.second->Velocity()->setX( -( obj.second->Velocity()->getY() ) * tx * dpTan1 + nx * m1 );
		}

		if (obj.second->isMovable() == true)
		{
			obj.second->Velocity()->setX(tx * dpTan2 + nx * m2);
			obj.second->Velocity()->setY(ty * dpTan2 + ny * m2);

		}
		else
		{
			//obj.first->Velocity()->setX( -( obj.first->Velocity()->getX() ) * tx * dpTan1 + nx * m1 );
			
			//obj.first->Velocity()->setX( -( obj.first->Velocity()->getY() ) * tx * dpTan1 + nx * m1 );
		}
		/*
		// Normal
		float nx = (obj.second->Pos()->getX() - obj.first->Pos()->getX()) / fDistance;
		float ny = (obj.second->Pos()->getY() - obj.first->Pos()->getY()) / fDistance;
		
		
		float kx = ( obj.first->Velocity()->getX() - obj.second->Velocity()->getY() );
		float ky = ( obj.first->Velocity()->getX() - obj.second->Velocity()->getY() );

		float p = 2.0 * (nx * kx + ny * ky) / ( obj.first->getMass() + obj.second->getMass() );

		if ( obj.first->isMovable() == true )
		{ 
			obj.first->Velocity()->addX( ( p * obj.second->getMass() * nx ) );
			obj.first->Velocity()->addY( ( p * obj.second->getMass() * ny ) );
		}

		if( obj.second->isMovable() == true )
		{ 
			obj.second->Velocity()->addX( -( p * obj.first->getMass() * nx ) );
			obj.second->Velocity()->addY( -( p * obj.first->getMass() * ny ) );
		}*/
		/*
		// Tangent
		float tx = -ny;
		float ty = nx;

		// Dot Product Tangent
		float dpTan1 = dotProduct( obj.first->Velocity()->getX(), obj.first->Velocity()->getY(), tx, ty );
		float dpTan2 = dotProduct( obj.second->Velocity()->getX(), obj.second->Velocity()->getY(), tx, ty );

		// Dot Product Normal
		float dpNorm1 = dotProduct( obj.first->Velocity()->getX(), obj.first->Velocity()->getY(), nx, ny );
		float dpNorm2 = dotProduct( obj.second->Velocity()->getX(), obj.second->Velocity()->getY(), nx , ny );

		// Conservation of momentum in 1D
		float m1 = (dpNorm1 * (obj.first->getMass() - obj.second->getMass() ) + 2.0f * obj.second->getMass() * dpNorm2) / (obj.first->getMass() + obj.second->getMass());
		float m2 = (dpNorm2 * (obj.second->getMass() - obj.first->getMass() ) + 2.0f * obj.first->getMass() * dpNorm1) / (obj.first->getMass() + obj.second->getMass());
		
		// Update velocities
		if ( obj.first->getType() != tPusher)
		{ 
			obj.first->Velocity()->setX(tx * dpTan1 + nx * m1);
			obj.first->Velocity()->setY(ty * dpTan1 + ny * m1);
		}

		if ( obj.second->getType() != tPusher)
		{
			obj.second->Velocity()->setX(tx * dpTan2 + nx * m2);
			obj.second->Velocity()->setY(ty * dpTan2 + ny * m2);
	
		}
		*/
	}
}
