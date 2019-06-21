#pragma once

class SoundEfx
{
	Mix_Chunk* sound;

public:
	SoundEfx( std::string path );
	~SoundEfx();

	void play();

};

