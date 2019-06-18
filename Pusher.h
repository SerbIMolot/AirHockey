#pragma once

#include "stdafx.h"

class Pusher : public Entity
{




public:
	Pusher();
	~Pusher();

	//void Update(int x, int y);

	Circle collisionCircle;
	//void Update(std::shared_ptr< Object > obj = nullptr);

	void Draw();
//	void collisionDetected( std::shared_ptr< Object > obj ) ;

	void move( );

	void Update( std::shared_ptr< Object > obj = nullptr ) override;

	void collisionDetected( std::shared_ptr< Object > obj ) override;

};
