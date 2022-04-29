#pragma once
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>

class Scene
{
private:
	SDL_Surface* loadImageToSurface(std::string path, SDL_PixelFormat* format);
	std::list<Sprite *> m_sprites;
	int m_W;
	int m_H;
public:
	Scene(int weight, int height);
	void AddSprite(Sprite *newSprite);
	void RemoveSprite(Sprite* existingSprite);
	SDL_Surface* DrawInSurface(SDL_PixelFormat* format);
};
