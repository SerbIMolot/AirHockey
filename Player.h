#pragma once
class Player : public Entity
{
	float speed;
public:
	Player();
	~Player();

	void handleEvent(SDL_Event& e);

	void move();

	void Attack();

	bool outOfBounds();

	void Update(Object * obj = nullptr);

	void Draw();
	void collisionDetected(Object * obj);
};

