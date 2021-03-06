#pragma once
#include <iostream>
#undef main
#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>

namespace fs = std::filesystem;

class RenderingEngine
{
private:
	const int SCREEN_WIDTH = 1162;
	const int SCREEN_HEIGHT = 778;

	//Singleton implementation static member
	static RenderingEngine *instance;
	//Private constructor to prevent instance creation
	RenderingEngine();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;


public:
	//Get the Singleton static instance, if is not created it will create the instance
	static RenderingEngine *getInstance();

	void initSDL();
	void logSDLError(std::ostream &os, const std::string &msg);
	void cleanup();
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

	/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The m_renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
		SDL_Rect *clip = nullptr);

		/**
	* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
	* the texture's width and height and taking a clip of the texture if desired
	* If a clip is passed, the clip's width and height will be used instead of
	*	the texture's
	* @param tex The source texture we want to draw
	* @param ren The m_renderer we want to draw to
	* @param x The x coordinate to draw to
	* @param y The y coordinate to draw to
	* @param clip The sub-section of the texture to draw (clipping rect)
	*		default of nullptr draws the entire texture
	*/
		void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
			SDL_Rect *clip = nullptr);

	
	void startEngine();
};

