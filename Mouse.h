#pragma once
class Mouse : public Object
{

public:
	Mouse();
	~Mouse();
	/*
	void Mouse::updatePosition() 
	{
		
		updateVelocity();
		
		Pos( xPos + xVel );

	}

	void Mouse::updateVelocity() 
	{
		
		updateAccel();
		
		Velocity( Velocity() + Acceleration() );
	
	}

	void Mouse::updateAccel() 
	{
	
		Acceleration( Pos() - prevMouseX) / someConstant ); //or whatever formula works best

	}
*/



	void Update( int x, int y, bool isReleased, int button );

	void Draw();

	void collisionDetected( std::shared_ptr < Object > obj );

};

