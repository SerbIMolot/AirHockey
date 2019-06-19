#include "stdafx.h"
#include "Collision.h"

std::vector< std::shared_ptr< Object > > Collision::Objects = std::vector < std::shared_ptr< Object > >();

Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::addObject( std::shared_ptr< Object > obj )
{

	Objects.push_back( std::move( obj ) );

}

void Collision::addCollidedObject(  std::shared_ptr< Object > obj1, std::shared_ptr< Object > obj2 )
{
	//if ( collidedObjects.count( obj1 ) == 0 && collidedObjects.count( obj2 ) == 0
	//	&& obj1->getType() != tMouse && obj2->getType() != tMouse )
	//{
		collidedObjects[obj1] = obj2;

		obj1->collisionDetected( obj2 );

		obj2->collisionDetected( obj1 );

	//}
	
}

void Collision::Update()
{
	for( auto obj1 : Objects )
	{
		for( auto obj2 : Objects )
		{
			if ( obj1 == obj2 )
			{
				continue;
			}

			if ( collisionCheck( obj1, obj2 ) )
			{
				//std::cout << "COLLISIOM" << std::endl;
				addCollidedObject( obj1, obj2 );
				staticColisionRes();

			}

		}
	}

	
	dynamicColisionRes();

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

	float distX = abs( circ->Pos()->getX() - rect->Pos()->getX() );
	float distY = abs( circ->Pos()->getY() - rect->Pos()->getY() );

	if( distX > rect->w / 2 + circ->getRadius() )
	{
		return false;
	}

	if( distY > rect->h / 2 + circ->getRadius() )
	{
		return false;
	}
	if( distX <= rect->w / 2 + circ->getRadius() )
	{
		return true;
	}

	if( distY <= rect->h / 2 + circ->getRadius() )
	{
		return true;
	}

	float cornedDist = distance( distX, distY, rect->w / 2, rect->h / 2 );

	if( cornedDist <= ( circ->getRadius() * circ->getRadius() ) )
	{
		return true;
	}

	return false;

}
float Collision::circleCircleOverlap( std::shared_ptr<Circle> circ1, std::shared_ptr<Circle> circ2 )
{

	return distance( circ1->Pos(), circ2->Pos() ) - circ1->getRadius() - circ2->getRadius();

}

float Collision::circRectOverlap(std::shared_ptr<Circle> circ, std::shared_ptr<Rectangle> rect)
{

	//if ()
	float nearestRectEdge = 0;

	if ( abs( circ->Pos()->getY() - rect->topSide() ) > abs( circ->Pos()->getY() - rect->BottomSide() ) )
	{
		nearestRectEdge = rect->BottomSide();
	}
	else
	{
		nearestRectEdge = rect->topSide();
	}

	float leftBound;
	float rightBound;

	if( circ->Pos()->getY() >= rect->topSide() && circ->Pos()->getY() <= rect->BottomSide() )
	{
		leftBound = std::max( -circ->getRadius() + circ->Pos()->getX(), rect->LeftSide() );
		rightBound = std::min( circ->getRadius() + circ->Pos()->getX(), rect->RightSide() );
	}
	else
	{
		float num = sqrtf( circ->getRadius() * circ->getRadius() - pow( abs( nearestRectEdge - circ->Pos()->getY() ), 2 ) + circ->Pos()->getX() );
		leftBound = std::max( -num , rect->LeftSide() );
		rightBound = std::min( num , rect->RightSide() );
	}
	Vector2d vec;
	float distX = abs(circ->Pos()->getX() - rect->Pos()->getX());
	float distY = abs(circ->Pos()->getY() - rect->Pos()->getY());

	float cornedDist = distance(distX, distY, rect->w / 2, rect->h / 2);

	if (cornedDist <= (circ->getRadius() * circ->getRadius()))
	{
		//return true;
	}
	return   distance(distX, distY, rect->w / 2, rect->h / 2);

	//return  distance( distX, distY, rect->w / 2, rect->h / 2 ) - circ->getRadius();
}

bool Collision::pointCircleCollision( std::shared_ptr< Vector2d > vec, std::shared_ptr< Circle > circ)
{
	if ( distance( vec, circ->getVec() ) < circ->getRadius() )
	{

		return true;

	}

	return false;
}

void Collision::staticColisionRes()
{

	float overlapMultp = 0.5f;
	float overlap = 0;

	for ( auto obj : collidedObjects )
	{ 
		float pDistance = distance( obj.first->Pos(), obj.second->Pos() );

		if ( obj.first->isMovable() == true || obj.second->isMovable() == true )
		{
			overlapMultp = 1.0f;
		}
		
		//float overlap = 0.5f * (pDistance - std::static_pointer_cast< Circle >( obj.first->getColShape()->getFirst() )->getRadius() - std::static_pointer_cast< Circle >( obj.second->getColShape()->getFirst() )->getRadius() );
		if ( obj.first->getColShape()->getCircle() != nullptr && obj.second->getColShape()->getCircle() != nullptr )
		{
			std::cout << "CIRCLE CIRCLE" << std::endl;
			overlap = overlapMultp * circleCircleOverlap( obj.first->getColShape()->getCircle(), obj.second->getColShape()->getCircle() );

		}

		if ( obj.first->getColShape()->getCircle() != nullptr && obj.second->getColShape()->getRectangle() != nullptr )
		{
			std::cout << "CERCLE RECT" << std::endl;
			overlap = overlapMultp * circRectOverlap( obj.first->getColShape()->getCircle(), obj.second->getColShape()->getRectangle() );

		}

		if ( obj.first->getColShape()->getRectangle() != nullptr && obj.second->getColShape()->getCircle() != nullptr )
		{
			std::cout << "RECT CIRCLE" << std::endl;
			overlap = overlapMultp * circRectOverlap( obj.second->getColShape()->getCircle(), obj.first->getColShape()->getRectangle() );

		}

		if ( obj.first->isMovable() == true )
		{ 
			obj.first->Pos()->addX( -( overlap * ( obj.first->Pos()->getX() - obj.second->Pos()->getX() ) / pDistance ) );
			obj.first->Pos()->addY( -( overlap * ( obj.first->Pos()->getY() - obj.second->Pos()->getY() ) / pDistance ) );
		}
		else
		{
			obj.second->Pos()->addX( (overlap * (obj.first->Pos()->getX() - obj.second->Pos()->getX() ) ) / pDistance );
			obj.second->Pos()->addY( (overlap * (obj.first->Pos()->getY() - obj.second->Pos()->getY() ) ) / pDistance );
		}

		if ( obj.second->isMovable() == true )
		{
			obj.second->Pos()->addX( (overlap * (obj.first->Pos()->getX() - obj.second->Pos()->getX() ) ) / pDistance );
			obj.second->Pos()->addY( (overlap * (obj.first->Pos()->getY() - obj.second->Pos()->getY() ) ) / pDistance );
		}
		
		/*
		if ( obj.first->isMovable() == true )
		{ 
			obj.first->Pos()->addX( -( overlap * ( obj.first->Pos()->getX() - obj.second->Pos()->getX() ) / pDistance ) );
			obj.first->Pos()->addY( -( overlap * ( obj.first->Pos()->getY() - obj.second->Pos()->getY() ) / pDistance ) );
		}
		else
		{
			obj.second->Pos()->addX( (overlap * (obj.first->Pos()->getX() - obj.second->Pos()->getX() ) ) / pDistance );
			obj.second->Pos()->addY( (overlap * (obj.first->Pos()->getY() - obj.second->Pos()->getY() ) ) / pDistance );
		}

		if ( obj.second->isMovable() == true )
		{
			obj.second->Pos()->addX( (overlap * (obj.first->Pos()->getX() - obj.second->Pos()->getX() ) ) / pDistance );
			obj.second->Pos()->addY( (overlap * (obj.first->Pos()->getY() - obj.second->Pos()->getY() ) ) / pDistance );
		}
		*/
		obj.second->getColShape()->Update( obj.second->Pos() );
		obj.first->getColShape()->Update( obj.first->Pos() );
	
	}
}

void Collision::dynamicColisionRes()
{
	for (auto obj : collidedObjects)
	{
		float fDistance = distance( obj.first->Pos(), obj.second->Pos() );
		
		// Normal
		float nx = (obj.second->Pos()->getX() - obj.first->Pos()->getX()) / fDistance;
		float ny = (obj.second->Pos()->getY() - obj.first->Pos()->getY()) / fDistance;

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
		if ( obj.first->getType() != tPusher && obj.first->isMovable() == true )
		{ 
			obj.first->Velocity()->setX(tx * dpTan1 + nx * m1);
			obj.first->Velocity()->setY(ty * dpTan1 + ny * m1);
		}

		if ( obj.second->getType() != tPusher && obj.second->isMovable() == true )
		{
			obj.second->Velocity()->setX(tx * dpTan2 + nx * m2);
			obj.second->Velocity()->setY(ty * dpTan2 + ny * m2);
	
		}
	}
}
