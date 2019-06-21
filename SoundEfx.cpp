#include "stdafx.h"
#include "SoundEfx.h"


SoundEfx::SoundEfx( std::string path )
{
	sound = Mix_LoadWAV( path.c_str() );

	if ( sound  == nullptr )
	{
		printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}
}


SoundEfx::~SoundEfx()
{
	Mix_FreeChunk( sound );
}

void SoundEfx::play()
{
	Mix_PlayChannel( -1, sound, 0 );
}
