#pragma once
#include "stdafx.h"

class Circle : public Shape
{

	int radius;

public:
	Circle( std::shared_ptr< Vector2d >, std::shared_ptr< Texture > );

	Circle(int x, int y, std::shared_ptr< Texture > );

	Circle(int x = 0, int y = 0, int radius = 3 );

	Circle( std::shared_ptr< Vector2d >, int radius);

	float upperCircle(float x);

	double lowerCircle(float x);




	void setVec( std::shared_ptr< Vector2d > vec );
	std::shared_ptr< Vector2d > getVec();


	void setRadius( int rad );
	int getRadius();
};
