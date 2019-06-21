#pragma once
#include "Shape.h"

class Circle : public Shape
{

	float radius;

public:
	Circle( std::shared_ptr< Vector2d >, std::shared_ptr< Texture > );

	Circle(int x, int y, std::shared_ptr< Texture > );

	Circle(float x, float y, float radius );
	Circle(int x = 0, int y = 0, int radius = 0 );

	Circle( std::shared_ptr< Vector2d >, int radius);

	float upperCircle(float x);

	double lowerCircle(float x);


	void setVec( std::shared_ptr< Vector2d > vec );
	std::shared_ptr< Vector2d > getVec();


	void setRadius( float rad );
	void setRadius( int rad );

	float getRadius();
};
