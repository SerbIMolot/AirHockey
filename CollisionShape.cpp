#include "stdafx.h"
#include "CollisionShape.h"


CollisionShape::CollisionShape()
{
	colShape = std::vector< std::shared_ptr< Shape > >();
}


CollisionShape::~CollisionShape()
{
}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec)
{
	std::shared_ptr< Shape > point = std::make_shared< Shape >( vec, sPoint );
	colShape.push_back( point );
}

void CollisionShape::addShape(int x, int y)
{
	std::shared_ptr< Shape > point = std::make_shared< Shape >( static_cast< float >( x ), static_cast< float >( y ), sPoint );
	colShape.push_back( point );
}

void CollisionShape::addShape( float x, float y, float w, float h )
{
	std::shared_ptr< Shape > rect = std::make_shared< Rectangle >( x, y, w, h );
	colShape.push_back( rect );

}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, float w, float h)
{
	std::shared_ptr< Shape > rect = std::make_shared< Rectangle >(vec, w, h );
	colShape.push_back(rect);

}

void CollisionShape::addShape(float x, float y, float r)
{
	std::shared_ptr< Shape > circ = std::make_shared< Circle >( x, y, r );
	colShape.push_back( circ );

}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, float r)
{
	std::shared_ptr< Shape > circ = std::make_shared< Circle >( vec, r );
	colShape.push_back( circ );

}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, std::shared_ptr<Texture> textr, cShape shType)
{
	
	if ( shType == sCircle )
	{
		std::shared_ptr< Shape > circ = std::make_shared< Circle >(vec, textr);
		colShape.push_back( circ );

	}
	if ( shType == sBox )
	{
		std::shared_ptr< Shape > rect = std::make_shared< Rectangle >( vec, textr );
		colShape.push_back( rect );

	}
}

void CollisionShape::Update( std::shared_ptr< Vector2d > vec )
{
	for( auto sh : colShape )
	{
		sh->Update( vec );
	}
}

void CollisionShape::Update(float x, float y)
{
	for (auto sh : colShape)
	{
		sh->Update( x, y );
	}
}

std::vector< std::shared_ptr< Shape > > CollisionShape::getShapes()
{
	return colShape;
}

std::shared_ptr< Shape > CollisionShape::getFirst()
{

	return colShape.front();

}

std::shared_ptr< Circle > CollisionShape::getCircle( int index )
{
	if ( index >= 0 )
	{
		if ( colShape[ index ]->getType() != sCircle )
		{
			return nullptr;
		}

		return std::static_pointer_cast< Circle >( colShape[ index ] );
	
	}

	return nullptr;

}

std::shared_ptr< Rectangle > CollisionShape::getRectangle( int index )
{
	if (index >= 0)
	{
		if ( colShape[index]->getType() != sBox )
		{
			return nullptr;
		}
		
		return std::static_pointer_cast< Rectangle >( colShape[ index ] );

	}

	return nullptr;

}

std::shared_ptr< Shape > CollisionShape::getPoint( int index )
{
	if ( index >= 0 )
	{
		if ( colShape[ index ]->getType() != sPoint )
		{
			return nullptr;
		}

		return std::static_pointer_cast< Shape >( colShape[ index ] );

	}

	return nullptr;

}