#pragma once

#include "stdafx.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(std::string path);

	bool loadFromFile(std::string path, SDL_Color colorKey );

	bool loadFromText( std::string textureText, SDL_Color textColor );

	void free();

	void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	void render( float x, float y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	void render( std::shared_ptr< Vector2d > vec, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	//Color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Blending
	void setBlendMode( SDL_BlendMode blending );

	//Alpha modulation
	void setAlpha( Uint8 alpha );

	int getWidth();
	int getHeight();

private:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

