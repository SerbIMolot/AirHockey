#pragma once

#include <map>

class TextureManager {
	static TextureManager* tmInstance;

	static std::map<std::string, std::shared_ptr<Texture>> Textures;

	TextureManager();

public:

	~TextureManager();

	static void addTexture(const char* path);
	static void addText(std::string textureText, SDL_Color textColor = { 0, 0, 0 }, std::string name = std::string());
	static TextureManager* Initialize();
	static void Close(std::string fileName);

	static std::shared_ptr<Texture> getTexture(const char * fileName);
	void loadTextures();
};


