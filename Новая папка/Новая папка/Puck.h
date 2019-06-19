#pragma once

#include "stdafx.h"

class Puck : public Entity
{
	//std::shared_ptr< Vector2d > aceleration;

	Circle collCirc;
public:
	Puck();
	~Puck();

	void moveTo(float x1, float y1, float x2, float y2);

	void Update(std::shared_ptr< Object > obj = nullptr) override;
	void move();
	void Draw();
	void collisionDetected(std::shared_ptr< Object > obj) override;


};

