#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	setMoveBounds( SCREEN_WIDTH, SCREEN_HEIGHT );
	setVelocity( 0, 0 );
	std::cout << "PL S" << std::endl;
	setSkin(TextureManager::getTexture("Hero.png"), tPlayer);
	Pos().setX(SCREEN_WIDTH / 2);
	Pos().setY(SCREEN_HEIGHT / 2);

	std::cout << "PL E" << std::endl;
}


Player::~Player()
{
}

void Player::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: setVelocity(getVelocity() + vecUP); break;
		case SDLK_DOWN: setVelocity(getVelocity() + vecDOWN); break;
		case SDLK_LEFT: setVelocity(getVelocity() + vecLEFT); break;
		case SDLK_RIGHT: setVelocity(getVelocity() + vecRIGHT); break;
		}
		//setVelocity( getVelocity() * speed );
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: setVelocity(getVelocity() - vecUP); break;
		case SDLK_DOWN: setVelocity(getVelocity() - vecDOWN); break;
		case SDLK_LEFT: setVelocity(getVelocity() - vecLEFT); break;
		case SDLK_RIGHT: setVelocity(getVelocity() - vecRIGHT); break;
		}
		//setVelocity( getVelocity() * speed );
	}
}

void Player::move()
{
}


void Player::Attack()
{
}

bool Player::outOfBounds()
{

	if (Pos(world).getX() + getSkin().getWidth() > getMoveBounds().getX() || Pos(world).getX() < 0) {

		//Pos(world).setX(Pos(world).getX() - getVelocity().getX() * timer->DeltaTime());
		printf("Out of bounds x \n");
		Pos(world).setX(Pos(world).getX() - getVelocity().getX());
		//UpdateBox();
		return true;
	}
	if (Pos(world).getY() + getSkin().getHeight() > getMoveBounds().getY() || Pos(world).getY() < 0) {

		//Pos(world).setY(Pos().getY() - vel.getY() * timer->DeltaTime());
		printf("Out of bounds y \n");
		Pos(world).setY(Pos().getY() - getVelocity().getY());
		//UpdateBox();
		return true;
	}
	return false;
}

void Player::Update(Object * obj)
{
	printf("Player pos: \n x: %lf, y: %lf \n", Pos().getX(), Pos().getY());
	if (  !outOfBounds() )
	{
		Pos( Pos() + getVelocity() );
	}
}

void Player::Draw()
{
		getSkin().render(Pos() - Camera::Instance()->Pos());
}

void Player::collisionDetected(Object * obj)
{
}
