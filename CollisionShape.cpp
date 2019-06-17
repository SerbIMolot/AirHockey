#include "stdafx.h"
#include "CollisionShape.h"


CollisionShape::CollisionShape()
{
	colShape = std::vector< std::shared_ptr< Shape > >();
}


CollisionShape::~CollisionShape()
{
}

void CollisionShape::addShape( float x, float y, float w, float h )
{
	std::shared_ptr< Shape > rect = std::make_shared< Rectangle >( x, y, w, h );
	colShape.push_back( rect );
	//Rectangle rect( x, y, w, h );
	//colShape.push_back( std::static_pointer_cast< Shape >( std::make_shared< Rectangle >( rect ) ) );
}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, float w, float h)
{
	std::shared_ptr< Shape > rect = std::make_shared< Rectangle >(vec, w, h );
	colShape.push_back(rect);
	//Rectangle rect( vec, w, h );
	//colShape.push_back( std::make_shared< Rectangle >( rect ) );
}

void CollisionShape::addShape(float x, float y, float r)
{
	std::shared_ptr< Shape > circ = std::make_shared< Circle >( x, y, r );
	colShape.push_back( circ );
	//Circle circ( x, y, r );
	//colShape.push_back( std::make_shared< Circle >( circ ) );
}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, float r)
{
	std::shared_ptr< Shape > circ = std::make_shared< Circle >( vec, r );
	colShape.push_back( circ );
	//Circle circ( vec, r );
	//colShape.push_back( std::make_shared< Circle >( circ ) );
}

void CollisionShape::addShape(std::shared_ptr<Vector2d> vec, std::shared_ptr<Texture> textr, cShape shType)
{
	
	if ( shType == sCircle )
	{
		std::shared_ptr< Shape > circ = std::make_shared< Circle >(vec, textr);
		colShape.push_back( circ );
		//Circle circ( vec, textr );
		//colShape.push_back( std::make_shared< Circle >( circ ) );
	}
	if ( shType == sBox )
	{
		std::shared_ptr< Shape > rect = std::make_shared< Rectangle >( vec, textr );
		colShape.push_back( rect );

		//colShape.push_back( std::static_pointer_cast< Shape >( std::make_shared< Rectangle >( rect ) ) );
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