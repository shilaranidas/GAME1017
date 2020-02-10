#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#define WIDTH 1024
#define HEIGHT 668
#define FPS 60
using namespace std;

// Global engine variables.
bool g_bRunning = false; // Loop control flag.
int g_iSpeed = 5; // Speed of box.
const Uint8* g_iKeystates; // Keyboard state container.
Uint32 g_start, g_end, g_delta, g_fps; // Fixed timestep variables.
SDL_Window* g_pWindow; // This represents the SDL window.
SDL_Renderer* g_pRenderer; // This represents the buffer to draw to.

bool init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (g_pWindow != nullptr) // Window init success.
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer != nullptr) // Renderer init success.
			{

			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	g_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	g_iKeystates = SDL_GetKeyboardState(nullptr);

	g_bRunning = true; // Everything is okay, start the engine.
	cout << "Success!" << endl;
	return true;
}

void wake()
{
	g_start = SDL_GetTicks();
}

void sleep()
{
	g_end = SDL_GetTicks();
	g_delta = g_end - g_start;
	if (g_delta < g_fps) // Engine has to sleep.
		SDL_Delay(g_fps - g_delta);
}

void handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			g_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_bRunning = false;
			break;
		}
	}
}

// Keyboard utility function.
bool keyDown(SDL_Scancode c)
{
	if (g_iKeystates != nullptr)
	{
		if (g_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void update()
{

}

void render()
{
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer); // Clear the screen with the draw color.
	// Render stuff.

	// Draw anew.
	SDL_RenderPresent(g_pRenderer);
}

void clean()
{
	cout << "Cleaning game." << endl;
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}

// Main function.
int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	if (init("GAME1007_SDL_Setup", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (g_bRunning)
	{
		wake();
		handleEvents();
		update();
		render();
		if (g_bRunning)
			sleep();
	}
	clean();
	return 0;
}