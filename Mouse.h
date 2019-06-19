#pragma once
class Mouse : public Object
{

	std::shared_ptr< Object > grabbedObj;

	bool LMBHold;
	bool RMBHold;

public:
	Mouse();
	~Mouse();

	void grabObj( std::shared_ptr< Object > obj );
	void releaseObj();

	void UpdateStats( int x, int y, bool isReleased, int button );

	void Update();

	void Draw();

	void collisionDetected( std::shared_ptr < Object > obj );

};

