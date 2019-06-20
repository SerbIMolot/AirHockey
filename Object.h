#pragma once
#ifndef OBJECT_H
#define OBJECT_H


enum SPACE { world = 0, screen = 1 };

enum Type {
	tUndefined,
	tPlayer,
	tEnemy,
	tObject,
	tPusher,
	tPuck,
	tMouse,
	tWall
};


class Object {
private:
	int id;
	Type type;
	std::shared_ptr< Vector2d > previousPos;
	std::shared_ptr< Vector2d > position;
	std::shared_ptr< Vector2d > velocity;
	std::shared_ptr< Vector2d > acceleration;

	float speed;

	std::shared_ptr< Shape > collisionShape;

	std::shared_ptr< CollisionShape > colShape;

	float mass;

	std::shared_ptr< Vector2d > previousVel;
	std::shared_ptr< Timer > timer;

	float rotation;

	bool active;

	std::shared_ptr<Texture> skin;

	std::shared_ptr< Circle > collisionCircle;

	bool movable;


	float phSimTimeRemein;

	Rectangle bounds;


public:
	float maxA;
	/*
	void Object::updatePosition() 
	{
	
		updateVelocity();
		
		Pos( Pos() + getVelocity() );
	
	}

	void Object::updateVelocity() {
		updateAccel();
		xVel = xVel + xAccel;
	}

	void Object::updateAccel() {
		xAccel = ( currentMouseX - prevMouseX ) / someConstant; //or whatever formula works best
	}
	*/


	Object();

	Object(float x, float y, float h, float w, Type type = tWall, cShape shape = sBox);

	//Object(float x, float y, float h, float w, Type type = tWall, cShape shape = sBox);


	Object( float x, float y, std::shared_ptr<Texture> texture, Type type, cShape shape );

	Object( std::shared_ptr< Vector2d > vec, std::shared_ptr<Texture> texture, Type type, cShape shape );

	~Object();

	std::shared_ptr<Vector2d> prevPos();

	void prevPos(std::shared_ptr<Vector2d> vec);

	void prevPos(int x, int y);

	std::shared_ptr<Vector2d> prevVel();

	void prevVel(std::shared_ptr<Vector2d> vec);

	void prevVel(int x, int y);

	
	
	void setMass( float x );

	void setMass( int x );

	float getMass();

	std::shared_ptr< Shape > getShape();

	//std::shared_ptr< Vector2d > Pos(SPACE space = world);

	void Active(bool active);
	bool Active();

	void updatePosition( float x = -1.0f, float y = -1.0f );


	void updateVelocity(float x, float y);

	void updateAccel(float x, float y);

	void setSkin(std::shared_ptr<Texture> texture, Type type);

	std::shared_ptr< Texture > getSkin();

	Type getType();

	void setType(Type type);
	void UpdateCircle();

	void Rotation(float r);

	float Rotation(SPACE space);

	void Update( std::shared_ptr< Object > obj = nullptr);

	virtual void Draw() = 0;

	virtual void collisionDetected( std::shared_ptr< Object > obj ) = 0;
// Getters
	std::shared_ptr<Vector2d> Pos();
	std::shared_ptr<Vector2d> Velocity();
	std::shared_ptr<Vector2d> Acceleration();
	std::shared_ptr<CollisionShape> getColShape();

	float getSimTimeRem();

	bool isMovable();

	float getSpeed();

// Setters
	void Pos(std::shared_ptr< Vector2d > vec);
	void Pos(int x, int y);

	void Velocity(std::shared_ptr<Vector2d> vec);
	void Velocity(float x, float y);

	void Acceleration(std::shared_ptr<Vector2d> vec);
	void Acceleration(float x, float y);

	void setSimTimeRem( float t );

	void setMovable(bool mov);

	void setSpeed( float s );

	
	void moveTo( int x, int y );

	bool outOfBounds();

	friend class Entity;
	friend class Puck;
	friend class Pusher;

};
#endif


