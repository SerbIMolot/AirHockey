#pragma once

enum cShape
{
	sUndefined,
	sBox,
	sCircle,
	sPoint,
	sLine
};

class Shape
{

	std::shared_ptr< Vector2d > pos;

	cShape type;
	
public:

	Shape( cShape type = sUndefined );
	Shape( std::shared_ptr< Vector2d > vec, cShape type = sUndefined );
	Shape( float x, float y, cShape type = sUndefined);

	~Shape();

	void Update( std::shared_ptr< Vector2d > vec );
	
	void Update( float x, float y );

	std::shared_ptr< Vector2d > Pos();

	float getX();
	float getY();

	cShape getType();
	
};


