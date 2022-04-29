#include "Scene.h"

Scene::Scene(int weight, int height)
{
	m_W = weight;
	m_H = height;
}

void Scene::AddSprite(Sprite* newSprite)
{
	if (newSprite != NULL)
	{
		m_sprites.push_back(newSprite);
	}
}

void Scene::RemoveSprite(Sprite* existingSprite)
{
	if (existingSprite != NULL)
	{
		m_sprites.remove(existingSprite);
	}
}

SDL_Surface* Scene::DrawInSurface(SDL_PixelFormat* format)
{
	std::list<Sprite*>::iterator it;
    SDL_Surface* scene = NULL;
	for (it = m_sprites.begin(); it != m_sprites.end(); it++)
	{
        Sprite* currentSprite = *it;
        currentSprite->executeAction("normal");
        Image *currentImage = currentSprite->getCurrentAction()->getCurrentImage();
        scene = loadImageToSurface(currentImage->getPath() + currentImage->getName(), format);
	}
    return scene;
}

SDL_Surface* Scene::loadImageToSurface(std::string path, SDL_PixelFormat *format)
{
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}