#pragma once
class Line : public Shape
{
	std::shared_ptr< Vector2d > startPoint;
	std::shared_ptr< Vector2d > endPoint;

	float r;
public:

	Line( float x1, float y1, float x2, float y2 , float r = 0.0f );
	Line( std::shared_ptr< Vector2d > start, std::shared_ptr< Vector2d > end, float r = 0.0f );
	
	std::shared_ptr< Vector2d > getEndPoint();
	float getRadius();

	void setRadius(float r);

	~Line();





};

