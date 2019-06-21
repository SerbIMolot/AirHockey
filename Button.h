#pragma once
class Button
{
	std::shared_ptr< Vector2d > pos;
	std::shared_ptr< Rectangle > rect;

	bool pressed;

	std::string text;

	static std::unique_ptr< NFont > buttonFont;
	std::unique_ptr< NFont > buttonFont1;
public:
	//Button();
	Button(std::shared_ptr<Vector2d> vec, float w, float h, std::string text);
	Button(int x, int y, int w, int h, std::string text);
	Button(float x, float y, float w, float h, std::string text);
	~Button();


public:

	std::shared_ptr< Rectangle > getRectangle();
	std::shared_ptr< Vector2d > Pos();

	void Draw();
	
	void collisionDetected( std::shared_ptr< Object > obj );

	bool isPressed();
};

