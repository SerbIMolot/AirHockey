#pragma once
class Enemy : public Entity
{
	std::shared_ptr< Puck > puck;
	float eSpeed;
	Timer etimer;
	std::default_random_engine generator;
	float maxMovementSpeed;
	std::shared_ptr< Vector2d > targetPos;
	float offsetXFromTarget;
	bool isFirstTimeInOpponentsHalf;
	Timer lastHit;
public:
	Enemy( );
	~Enemy();


	bool puckInCorner();

	void moveTo(float x1, float y1, float x2, float y2);

	void Attack();

	void defence();
	void doNothing();
	void makeDecision();
	//void Update();

	void followPuck();
	
	void moveTo(float x, float y);

	void Update(std::shared_ptr< Object > obj = nullptr );

	Vector2d predictPuck();
	void move();
	void Draw();

	void setPuck( std::shared_ptr< Puck > puck );

	void collisionDetected(std::shared_ptr< Object > obj) ;
};

