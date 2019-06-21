#pragma once




class Board
{
	std::shared_ptr< Wall > topWall;
	std::shared_ptr< Wall > leftWall;
	std::shared_ptr< Wall > bottomWall;
	std::shared_ptr< Wall > rightWall;

	
	std::shared_ptr< Object > playerGates;
	std::shared_ptr< Object > aiGates;

	std::unique_ptr< NFont > redFont;
	std::unique_ptr< NFont > blueFont;
	//NFont font;

	//std::unique_ptr< FC_Font > fFont;
	//FC_Font* fFont;
public:

	static int aiPoints;
	static int playerPoints;


	Board();
	~Board();
	void Draw();
};

