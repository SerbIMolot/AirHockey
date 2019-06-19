#pragma once
class Collision
{

	static std::vector< std::shared_ptr< Object > > Objects;

	std::map< std::shared_ptr< Object >, std::shared_ptr< Object > > collidedObjects;

	int numSimulationUpdates;

	float tSimulationElapsTime;

	int numMaxSimSteps;

public:
	Collision();
	~Collision();

	static void addObject(std::shared_ptr<Object> obj);

	void addCollidedObject(std::shared_ptr<Object> obj1, std::shared_ptr< Object > obj2 );

	void Update();

	bool collisionCheck(std::shared_ptr< Object > obj1, std::shared_ptr< Object > obj2);

	bool circleCollisionCheck(std::shared_ptr< Circle > circ1, std::shared_ptr< Circle > circ2);

	bool RectCollisionCheck(std::shared_ptr< Rectangle > rect, std::shared_ptr< Rectangle > rect2);

	bool circRectCollisionCheck( std::shared_ptr< Circle > circ, std::shared_ptr< Rectangle > rect);

	bool pointCircleCollision( std::shared_ptr<Vector2d> vec, std::shared_ptr<Circle> circ );

	bool lineCircleCollision( std::shared_ptr< Line > line, std::shared_ptr< Circle > circ );

	void staticColisionRes();


	void dynamicColisionRes();
};

