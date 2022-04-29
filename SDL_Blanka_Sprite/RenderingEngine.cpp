#include "RenderingEngine.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "Character.h"
#include "Scene.h"

RenderingEngine *  RenderingEngine::instance = 0;

RenderingEngine * RenderingEngine::getInstance()
{
	if (instance == 0)//means no instance has been created
	{
		instance = new RenderingEngine();
	}
	return instance;
}

//Singleton private constructor
RenderingEngine::RenderingEngine()
{
	//Action* actionTest = new Action("C:\\Users\\roberto.tellez\\source\\repos\\SDL_Blanka_Sprite\\x64\\Debug\\actions_test.xml");
	//Character* sprite1 = new Character("C:\\Users\\roberto.tellez\\source\\repos\\SDL_Blanka_Sprite\\SDL_Blanka_Sprite\\Resources\\Images\\Blanka\\blanka_sprite.xml");
	//std::cout << "Current path is " << fs::current_path() << '\n';
}


void RenderingEngine::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return;
	}

	m_window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup();
		SDL_Quit();
		return;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return;
	}

	Sprite* sprite1 = new Character("./Resources/Images/Blanka/blanka_sprite.xml");
	Scene* testScene = new Scene(800, 600);
	testScene->AddSprite(sprite1);
	testScene->DrawInSurface(SDL_GetWindowSurface(m_window)->format);
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The m_renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* RenderingEngine::loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

void RenderingEngine::logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void RenderingEngine::cleanup()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void RenderingEngine::startEngine()
{
	initSDL();
	std::string filePath = ".\\Resources\\Images\\Blanka\\Blanka1.png";
	std::string filePath2 = ".\\Resources\\Images\\Blanka\\Blanka2.png";
	std::string filePath3 = ".\\Resources\\Images\\Blanka\\Blanka3.png";
	std::string filePath4 = ".\\Resources\\Images\\Blanka\\Blanka4.png";
	std::string scenario = ".\\Resources\\Images\\Scenarios\\tlaxcala.png";
	SDL_Texture* tex = loadTexture(filePath, m_renderer);
	SDL_Texture* tex1 = loadTexture(filePath2, m_renderer);
	SDL_Texture* tex2 = loadTexture(filePath3, m_renderer);
	SDL_Texture* tex3 = loadTexture(filePath4, m_renderer);

	SDL_Texture* scenarioTex = loadTexture(scenario, m_renderer);

	
	int useClip = 0;
	SDL_Event e;
	bool quit = false;
	int texCounter = 0;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_1:
					useClip = 0;
					break;
				case SDLK_2:
					useClip = 1;
					break;
				case SDLK_3:
					useClip = 2;
					break;
				case SDLK_4:
					useClip = 3;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
				
			}
		}
		//Render the scene
		SDL_Delay(240);
		SDL_RenderClear(m_renderer);

		SDL_Rect clip, dest, scene, sceneScaled;
		clip.x = 0;
		clip.y = 230;
		//clip.w = 320;
		//clip.h = 418;
		clip.w = 397;
		clip.h = 518;

		dest.x = 0;
		dest.y = 0;
		dest.w = 397;
		dest.h = 518;

		scene.x = 0;
		scene.y = 0;
		scene.w = 1162;
		scene.h = 778;

		sceneScaled.x = 0;
		sceneScaled.y = 0;
		sceneScaled.w = 1162;
		sceneScaled.h = 778;

		renderTexture(scenarioTex, m_renderer, sceneScaled, &scene);

		if (texCounter == 0)
			renderTexture(tex, m_renderer, clip, &dest);
		else if (texCounter == 1)
			renderTexture(tex1, m_renderer, clip, &dest);
		else if (texCounter == 2)
			renderTexture(tex2, m_renderer, clip, &dest);
		else if (texCounter == 3)
			renderTexture(tex3, m_renderer, clip, &dest);
		else 
			renderTexture(tex, m_renderer, clip, &dest);

		if (texCounter == 4)
			texCounter = 0;
		texCounter++;
		SDL_RenderPresent(m_renderer);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(tex1);
	SDL_DestroyTexture(tex2);
	SDL_DestroyTexture(tex3);
	SDL_DestroyTexture(scenarioTex);

	cleanup();
	IMG_Quit();
	SDL_Quit();
}

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The m_renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void RenderingEngine::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
	SDL_Rect *clip)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

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
void RenderingEngine::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
	SDL_Rect *clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}