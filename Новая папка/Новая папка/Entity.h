#pragma once
class Entity : public Object
{
	

	
	std::shared_ptr< Vector2d > moveBounds;
	std::shared_ptr< Vector2d > velocity;

public:
	Entity();
	~Entity();

	void setMoveBounds( std::shared_ptr< Vector2d > bounds );
	void setMoveBounds( float x, float y );
	void setVelocity( std::shared_ptr< Vector2d > velocity );
	void setVelocity( float x, float y );

	std::shared_ptr< Vector2d > getMoveBounds();
	std::shared_ptr< Vector2d > getVelocity();


	virtual void move() = 0;

	virtual void Update( std::shared_ptr< Object > obj ) = 0;

	virtual void collisionDetected( std::shared_ptr< Object > obj ) = 0;
	friend class Puck;
};

