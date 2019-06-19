#pragma once
class Trigger
{
	static int triggerCount;
	int id;

	std::string name;

	std::shared_ptr< Vector2d > pos;

	std::shared_ptr< Rectangle > rect;

	bool triggered;

public:
	Trigger( std::shared_ptr< Vector2d > vec, int w, int h );
	Trigger( std::shared_ptr< Vector2d > vec, std::shared_ptr< Rectangle > rect );
	Trigger( int x, int y, int w, int h );

	void setName( std::string str );
	std::string getName(  );

	std::shared_ptr< Rectangle > getRect();


	~Trigger();

	bool isTrigered();
	void trigger();

	void reset();


};



