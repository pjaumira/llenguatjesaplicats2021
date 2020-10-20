//SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Generic includes
#include <exception>
#include <iostream>
#include <string>

//Include de extra variables
#include "Types.h"

int main(int, char* [])
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window* m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer* m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//-->SDL_Image
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() == -1) throw "No es pot inicialitzar SDL_ttf";

	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error amb SDL_Mixer init";

	// --- SPRITES ---
	//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//Mouse
	SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (cursorTexture == nullptr) throw "Error: cursorTexture init";
	SDL_Rect playerRect{ 0, 0, 100, 50 };

	//-->Animated Sprite ---

	// --- TEXT ---

	// --- AUDIO ---

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning)
	{
		// HANDLE EVENTS
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					isRunning = false;
				break;
			// Capturar el moviment del ratoli al Vector mouse
			case SDL_MOUSEMOTION:
				mouse.x = event.motion.x;
				mouse.y = event.motion.y;
				break;
			default:;
			}
		}

		// UPDATE

		// Suavitzem el moviment del ratoli perque el segueixi
		playerRect.x += (mouse.x - playerRect.x - playerRect.w / 2) / 10;
		playerRect.y += (mouse.y - playerRect.y - playerRect.h / 2) / 10;

		// DRAW
		//Neteja tot el renderer
		SDL_RenderClear(m_renderer);

		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		//Mouse
		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &playerRect);

		SDL_RenderPresent(m_renderer);
	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(cursorTexture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}