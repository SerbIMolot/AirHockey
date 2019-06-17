#pragma once

#include "stdafx.h"

class Puck : public Entity
{
	//std::shared_ptr< Vector2d > aceleration;

	Circle collCirc;
public:
	Puck();
	~Puck();

	void Update(std::shared_ptr< Object > obj = nullptr) override;
	void move();
	void Draw();
	void collisionDetected(std::shared_ptr< Object > obj) override;


};

