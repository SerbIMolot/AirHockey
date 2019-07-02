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
	if ( collidedObjects.count( obj1 ) == 0 && collidedObjects.count( obj2 ) == 0 
		 && obj1->getType() != tWall && obj2->getType() != tWall )
	{

		collidedObjects[obj1] = obj2;

		obj1->collisionDetected( obj2 );

		obj2->collisionDetected( obj1 );

	}
	
}

void Collision::Update()
{
	for( auto obj1 : Objects )
	{

		for ( auto tr : TriggersManager::Instance()->trigers )
		{
			if ( collisionCheck( tr, obj1 ) )
			{
				tr->trigger();

				TriggersManager::Instance()->collisionDetected( obj1 );
			}
		}

		for( auto obj2 : Objects )
		{
			if ( obj1 == obj2 )
			{
				continue;
			}

			if ( collisionCheck( obj1, obj2 ) )
			{

				if ( obj1->getType() == tMouse )
				{
					obj1->collisionDetected( obj2 );
					continue;
				}
				else if ( obj2->getType() == tMouse )
				{
					obj2->collisionDetected( obj1 );
					continue;
				}
				if ( obj1->getType() != tWall && obj2->getType() != tWall
					 )
				{
					printf(" collision %d\n", obj1->getType());
					printf(" collision %d\n", obj2->getType());


				}

				addCollidedObject( obj1, obj2 );
				
				

			}

		}
	}

	
	staticColisionRes();
	
	dynamicColisionRes();

	for (auto obj1 : Objects)
	{
		obj1->getColShape()->Update( obj1->Pos() );
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

				return circRectCollisionCheck( std::static_pointer_cast< Circle >( sh2 ), std::static_pointer_cast< Rectangle >( sh1 ) );
	
			}

			if ( sh1->getType() == sPoint && sh2->getType() == sBox )
			{

				return pointRectCollisionCheck( sh1 , std::static_pointer_cast< Rectangle >( sh2 ) );
	
			}

			if ( sh1->getType() == sBox && sh2->getType() == sPoint )
			{

				return pointRectCollisionCheck( sh2, std::static_pointer_cast< Rectangle >( sh1 ) );

			}

			if ( sh1->getType() == sPoint && sh2->getType() == sCircle)
			{

				return pointCircleCollisionCheck( sh1 , std::static_pointer_cast< Circle >( sh2 ) );
	
			}

			if ( sh1->getType() == sCircle && sh2->getType() == sPoint )
			{

				return pointCircleCollisionCheck( sh2, std::static_pointer_cast< Circle >( sh1 ) );

			}

		}

	}

	return false;

}

bool Collision::collisionCheck(std::shared_ptr< Button > button, std::shared_ptr< Object > obj)
{

	for (auto sh1 : obj->getColShape()->getShapes())
	{

		if (sh1->getType() == sPoint)
		{

			return pointRectCollisionCheck( sh1, button->getRectangle() );

		}

	}

	return false;
}

bool Collision::collisionCheck(std::shared_ptr< Trigger > tr, std::shared_ptr< Object > obj)
{

	for ( auto sh1 : obj->getColShape()->getShapes() )
	{

			if ( sh1->getType() == sBox )
			{

				return RectCollisionCheck( std::static_pointer_cast< Rectangle >(sh1), tr->getRect() );

			}

			if ( sh1->getType() == sCircle )
			{

				return circRectCollisionCheck( std::static_pointer_cast< Circle >( sh1 ), tr->getRect() );

			}

		}

	return false;
	
}

bool Collision::circleCollisionCheck(std::shared_ptr<Circle> circ1, std::shared_ptr<Circle> circ2)
{

	Vector2d n = *circ2->Pos() - *circ1->Pos();
	
	float radiusSqr = circ1->getRadius() + circ2->getRadius();
	radiusSqr *= radiusSqr;

	if ( n.lengthSqr() <= radiusSqr )
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
	// Find the closest point to the circle within the rectangle
	Vector2d normal = *circ->Pos() - *rect->Pos();
	Vector2d closestP = Vector2d( clamp( circ->getX(), rect->LeftSide(), rect->RightSide() ),
								  clamp( circ->getY(), rect->topSide(), rect->BottomSide() ) );

	// Calculate the distance between the circle's center and this closest point
	Vector2d distance = *circ->Pos() - closestP;

	// If the distance is less than the circle's radius, an intersection occurs
	return distance.lengthSqr() < (circ->getRadius() * circ->getRadius() );

}
float Collision::circleCircleOverlap( std::shared_ptr<Circle> circ1, std::shared_ptr<Circle> circ2 )
{

	return distance( circ1->Pos(), circ2->Pos() ) - circ1->getRadius() - circ2->getRadius();

}

float Collision::circRectOverlap(std::shared_ptr<Circle> circ, std::shared_ptr<Rectangle> rect)
{

	float NearestX = std::max(rect->getX(), std::min( circ->Pos()->getX(), rect->getX() + rect->w));
	float NearestY = std::max(rect->getY(), std::min( circ->Pos()->getY(), rect->getY() + rect->h));
	
	Vector2d dist = Vector2d(circ->getX() - NearestX, circ->getY() - NearestY);


	float penetrationDepth = circ->getRadius() - dist.magnitude();

	return penetrationDepth;

}

bool Collision::pointCircleCollisionCheck( std::shared_ptr< Shape > sh, std::shared_ptr< Circle > circ)
{
	if ( distanceSquared( sh->Pos(), circ->getVec() ) < circ->getRadius() * circ->getRadius() )
	{

		return true;

	}

	return false;
}

bool Collision::pointRectCollisionCheck( std::shared_ptr< Shape > sh, std::shared_ptr<Rectangle> rect )
{
	if ( sh->getX() > rect->LeftSide() && sh->getY() > rect->topSide()
		&& sh->getX() < rect->RightSide() && sh->getY() < rect->BottomSide() )
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
		std::shared_ptr< Vector2d > dist = std::make_shared< Vector2d >( ( obj.first->Pos()->getX() - obj.second->Pos()->getX() ), ( obj.first->Pos()->getY() - obj.second->Pos()->getY() ));
		float pDistance = distance( obj.first->Pos(), obj.second->Pos() );

		if ( obj.first->isMovable() == true || obj.second->isMovable() == true )
		{
			overlapMultp = 1.0f;
		}
		
		
		if ( obj.first->getColShape()->getCircle() != nullptr && obj.second->getColShape()->getCircle() != nullptr )
		{
			
			overlap = overlapMultp * circleCircleOverlap( obj.first->getColShape()->getCircle(), obj.second->getColShape()->getCircle() );

		}

		if ( obj.first->getColShape()->getCircle() != nullptr && obj.second->getColShape()->getRectangle() != nullptr )
		{
			
			float NearestX = std::max(obj.second->getColShape()->getRectangle()->getX(), std::min(obj.first->getColShape()->getCircle()->Pos()->getX(), obj.second->getColShape()->getRectangle()->RightSide() ));
			float NearestY = std::max(obj.second->getColShape()->getRectangle()->getY(), std::min(obj.first->getColShape()->getCircle()->Pos()->getY(), obj.second->getColShape()->getRectangle()->getY() + obj.second->getColShape()->getRectangle()->h ));
			dist = std::make_shared< Vector2d >( obj.first->getColShape()->getCircle()->getRadius() -  NearestX, obj.first->getColShape()->getCircle()->getRadius() - NearestY);
			pDistance = distance(obj.first->Pos(), dist);
			
			overlap = overlapMultp * circRectOverlap( obj.first->getColShape()->getCircle(), obj.second->getColShape()->getRectangle() );

		}

		if ( obj.first->getColShape()->getRectangle() != nullptr && obj.second->getColShape()->getCircle() != nullptr )
		{
			
			float NearestX = std::max(obj.first->getColShape()->getRectangle()->getX(), std::min(obj.second->getColShape()->getCircle()->Pos()->getX(), obj.first->getColShape()->getRectangle()->getX() + obj.first->getColShape()->getRectangle()->w ) );
			float NearestY = std::max(obj.first->getColShape()->getRectangle()->getY(), std::min(obj.second->getColShape()->getCircle()->Pos()->getY(), obj.first->getColShape()->getRectangle()->getY() + obj.first->getColShape()->getRectangle()->h ) );
			
			dist = std::make_shared< Vector2d >( obj.second->getColShape()->getCircle()->getRadius() - NearestX, obj.second->getColShape()->getCircle()->getRadius() - NearestY);
			
			pDistance = distance( obj.second->Pos(),  dist );
			
			overlap = overlapMultp * circRectOverlap( obj.second->getColShape()->getCircle(), obj.first->getColShape()->getRectangle() );

		}

		if ( obj.first->getColShape()->getPoint() != nullptr && obj.second->getColShape()->getCircle() != nullptr )
		{

			overlap = 0;

		}

		if ( obj.first->getColShape()->getPoint() != nullptr && obj.second->getColShape()->getRectangle() != nullptr )
		{

			overlap = 0;

		}

			
		if ( obj.first->isMovable() == true )
		{ 
			obj.first->Pos()->addX( -( overlap * dist->getX() / pDistance ) );
			obj.first->Pos()->addY( -( overlap * dist->getY() / pDistance ) );
		}


		if ( obj.second->isMovable() == true )
		{
			obj.second->Pos()->addX( ( overlap * dist->getX() ) / pDistance );
			obj.second->Pos()->addY( ( overlap * dist->getY() ) / pDistance );
		}
		
		
		obj.second->getColShape()->Update( obj.second->Pos() );
		obj.first->getColShape()->Update( obj.first->Pos() );
	
	}
}

void Collision::dynamicColisionRes()
{
	for (auto obj : collidedObjects)
	{

		float fDistance = 0;
		std::shared_ptr< Vector2d > dist = nullptr;
		Vector2d normal = Vector2d();
		if ( obj.first->getColShape()->getRectangle() != nullptr && obj.second->getColShape()->getCircle() != nullptr )
		{
			
			float NearestX = std::max(obj.first->getColShape()->getRectangle()->getX(), std::min(obj.second->getColShape()->getCircle()->getX(), obj.first->getColShape()->getRectangle()->RightSide() ) );
			float NearestY = std::max(obj.first->getColShape()->getRectangle()->getY(), std::min(obj.second->getColShape()->getCircle()->getY(), obj.first->getColShape()->getRectangle()->LeftSide() ) );
			
			dist = std::make_shared< Vector2d >(NearestX, NearestY);
			
			fDistance = distance( dist, obj.second->Pos() );


			normal = *obj.second->Pos() - *dist;
			
			normal /= fDistance;
		}

		if (obj.second->getColShape()->getRectangle() != nullptr && obj.first->getColShape()->getCircle() != nullptr)
		{
			std::shared_ptr< Vector2d > dist = nullptr;
			float NearestX = std::max(obj.second->getColShape()->getRectangle()->getX(), std::min(obj.first->getColShape()->getCircle()->Pos()->getX(), obj.second->getColShape()->getRectangle()->RightSide() ));
			float NearestY = std::max(obj.second->getColShape()->getRectangle()->getY(), std::min(obj.first->getColShape()->getCircle()->Pos()->getY(), obj.second->getColShape()->getRectangle()->LeftSide() ));
			
			dist = std::make_shared< Vector2d >(NearestX, NearestY);
			
			fDistance = distance(obj.first->Pos(), dist);

			normal = (*dist - *obj.first->Pos() );


			normal /= fDistance;

		}

		if ( obj.first->getColShape()->getCircle() != nullptr && obj.second->getColShape()->getCircle() != nullptr)
		{
			fDistance = distance(obj.first->Pos(), obj.second->Pos());
			
			normal = *obj.second->Pos() - *obj.first->Pos();

			normal /= fDistance;


		}

		Vector2d tang = normal;

		tang.rightHNormal();

		float dpTan1 = dotProduct(*obj.first->Velocity(), tang);

		float dpTan2 = dotProduct(*obj.second->Velocity(), tang);

		float dpNorm1 = dotProduct( *obj.first->Velocity(), normal );
		float dpNorm2 = dotProduct( *obj.second->Velocity(), normal );

		// Conservation of momentum in 1D
		float m1 = (dpNorm1 * (obj.first->getMass() - obj.second->getMass() ) + 2.0f * obj.second->getMass() * dpNorm2) / (obj.first->getMass() + obj.second->getMass());
		float m2 = (dpNorm2 * (obj.second->getMass() - obj.first->getMass() ) + 2.0f * obj.first->getMass() * dpNorm1) / (obj.first->getMass() + obj.second->getMass());
		
		// Update velocities
		if ( obj.first->getType() != tPusher && obj.first->isMovable() == true )
		{ 
			obj.first->Velocity( *( tang * dpTan1 ) + ( normal * m1 ) );
		}

		if ( obj.second->getType() != tPusher && obj.second->isMovable() == true )
		{

			obj.first->Velocity(*(tang * dpTan2) + (normal * m2));
	
		}

	}
}
