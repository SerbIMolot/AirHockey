#pragma once
#include "Texture.h"
class Rectangle : public Shape
{
public:

	float x;
	float y;
	float w;
	float h;

	Rectangle();
	Rectangle( int x, int y, int w, int h );
	Rectangle( float x, float y, float w, float h );
	Rectangle( std::shared_ptr< Vector2d > vec, float w, float h );
	Rectangle( std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> textr = nullptr);
	~Rectangle();

	std::shared_ptr< Vector2d > getVec();
	void setVec(std::shared_ptr< Vector2d > vec );

	float topSide();

	float BottomSide();

	float LeftSide();

	float RightSide();





};

