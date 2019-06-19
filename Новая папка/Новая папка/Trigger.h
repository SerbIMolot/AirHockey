#pragma once
class Trigger
{
	std::shared_ptr< Vector2d > pos;

	std::shared_ptr< Rectangle > rect;

	bool triggered;

public:
	Trigger( std::shared_ptr< Vector2d > vec, int w, int h );
	Trigger( std::shared_ptr< Vector2d > vec, std::shared_ptr< Rectangle > rect );
	Trigger( int x, int y, int w, int h );

	~Trigger();


};



