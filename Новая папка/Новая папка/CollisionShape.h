#pragma once
class CollisionShape
{
	std::vector< std::shared_ptr< Shape > > colShape;
public:
	CollisionShape();
	~CollisionShape();

	//Add rectangle
	void addShape( float x, float y, float w, float h );
	void addShape( std::shared_ptr< Vector2d > vec, float w, float h );

	//Add circle
	void addShape( float x, float y, float r );
	void addShape( std::shared_ptr< Vector2d > vec, float r );

	void addShape(std::shared_ptr< Vector2d > vec, std::shared_ptr< Texture > textr, cShape type);

	void Update( std::shared_ptr<Vector2d> vec );

	void Update( float x, float y );

	std::vector< std::shared_ptr< Shape > > getShapes();

	std::shared_ptr<Shape> getFirst();

	std::shared_ptr<Circle> getCircle( int index = 0 );

	std::shared_ptr<Rectangle> getRectangle( int index = 0 );

};

