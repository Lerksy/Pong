#include "TextureLoader.h"

void TextureLoader::initAssetFolder() {
	std::string dir = "asset";
	for (const auto& file : std::filesystem::directory_iterator(dir)) {
		std::filesystem::path filename = file.path().filename();
		if (filename.extension() == ".png") {
			buildTextureFromFile(filename.string());
		}
	}
}

void TextureLoader::initFont()
{
	font = TTF_OpenFont("fonts/ARCADECLASSIC.TTF", 24);
	if (font == nullptr) {
		std::cout << SDL_GetError();
	}
}

std::string TextureLoader::removeExtension(std::string filename) {
	return filename.substr(0, filename.find_last_of("."));
}

void TextureLoader::buildTextureFromFile(std::string filename) {
	std::string path = "asset/" + filename;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	textures.insert(std::make_pair(removeExtension(filename), tempTexture));
}

TextureLoader::TextureLoader(SDL_Renderer* renderer) {
	this->renderer = renderer;
	initAssetFolder();
	initFont();
}

SDL_Texture* TextureLoader::getTexture(std::string name) {
	return textures.at(name);
}

SDL_Texture* TextureLoader::renderText(std::string text) {
	auto textTexturesIterator = text_textures.find(text);

	if (textTexturesIterator != text_textures.end()) {
		return textTexturesIterator->second;
	}

	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
	SDL_Texture* ret = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	text_textures.insert(std::make_pair(text, ret));
	return ret;
}

TextureLoader::~TextureLoader()
{
	for (auto row : textures) {
		SDL_DestroyTexture(row.second);
	}
}
