#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::tmInstance = nullptr;

std::map< std::string, std::shared_ptr< SoundEfx > > SoundManager::Sounds;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	Close("all");
	delete tmInstance;
}

void SoundManager::addSound(const char * path)
{
	std::string temp = path;

	std::string fileName;

	if (temp.find_last_of("/") == -1)
	{
		fileName = temp;
	}

	fileName = temp.substr(temp.find_last_of("/") + 1, temp.size());

	int i = 0;

	for (auto s : Sounds)
	{
		if ( s.first == fileName )
		{
			i++;
		}
	}
	if (i != 0) {
		fileName += std::to_string(i);
	}

	printf("Sound effect : %s\n", fileName.c_str());
	Sounds[fileName] = std::make_shared< SoundEfx >( path );
	
}

SoundManager * SoundManager::Instance()
{
	if ( tmInstance == nullptr )
	{
		tmInstance = new SoundManager();
	}

	return tmInstance;
}

void SoundManager::Close(std::string fileName)
{

	if (fileName == "all") {

				Sounds.erase(fileName);
	}

	for ( auto s : Sounds ) {
		if ( s.first == fileName ) {

			Sounds.erase( fileName );
			break;
		}
	}


}

std::shared_ptr< SoundEfx > SoundManager::getSound(const char * fileName)
{
	if ( Sounds.find(fileName) == Sounds.end() ) {
		std::cout << "Could not find texture" << fileName << std::endl;
		return nullptr;
	}
	else {
		return Sounds[fileName];
	}
}

void SoundManager::loadSounds()
{
	addSound("Data/puck_hit.wav");
	addSound("Data/goal.wav");
}
