#pragma once
class SoundManager
{
	static SoundManager* tmInstance;

	static std::map<std::string, std::shared_ptr< SoundEfx > > Sounds;

	SoundManager();

public:

	~SoundManager();

	static void addSound(const char* path);
	
	static SoundManager* Instance();
	
	static void Close(std::string fileName);

	static std::shared_ptr< SoundEfx > getSound(const char * fileName);
	
	void loadSounds();
};


