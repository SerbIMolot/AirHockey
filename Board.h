#pragma once
class Board
{
	std::shared_ptr< Object > topWall;
	std::shared_ptr< Object > leftWall;
	std::shared_ptr< Object > bottomWall;
	std::shared_ptr< Object > rightWall;

	int aiPoints;
	int playerPoints;

	std::shared_ptr< Object > playerGates;
	std::shared_ptr< Object > aiGates;

public:
	Board();
	~Board();
};

