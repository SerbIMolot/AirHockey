#pragma once




class Board
{
	std::shared_ptr< Wall > topWall;
	std::shared_ptr< Wall > leftWall;
	std::shared_ptr< Wall > bottomWall;
	std::shared_ptr< Wall > rightWall;

	
	std::shared_ptr< Object > playerGates;
	std::shared_ptr< Object > aiGates;

public:

	static int aiPoints;
	static int playerPoints;


	Board();
	~Board();
	void Draw();
};

