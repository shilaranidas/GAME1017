#include <iostream>
#include "Engine.h"
#include <string.h>

#define WIDTH 1024
#define HEIGHT 668
#define FPS 60
using namespace std;

Engine::Engine() :m_bRunning(false), m_MousePos({ 0,0 })
{ 
	cout << "Engine class constructed!" << endl;
}
Engine::~Engine(){ delete m_pFSM; }

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				if (IMG_Init(IMG_INIT_PNG) != 0)
				{
					
				}
				else return false; // Image init fail.
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	
	m_pFSM = new FSM(); // Creates the state machine object/instance.
	m_pFSM->ChangeState(new TitleState()); // Invoking the ChangeState method to set the initial state, Title.
	m_bRunning = true; // Everything is okay, start the engine.
	cout << "Init success!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_bRunning = false;
			break;
		
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button >= 1 && event.button.button <= 3)
				m_MouseState[event.button.button - 1] = true;			
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button >= 1 && event.button.button <= 3)
				m_MouseState[event.button.button - 1] = false;			
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
			//SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
			break;
		}
	}
}

// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}
void Engine::Update()
{
	
	GetFSM().Update(); // Invokes the update of the state machine.
}

void Engine::Render()
{
	//std::cout << "getFSM " << GetFSM() << std::endl;
	auto a=GetFSM().GetStates();
	GetFSM().Render(); // Invokes the render of the state machine.
}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	GetFSM().Clean();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

int Engine::Run()
{
	if (m_bRunning) // What does this do and what can it prevent?
		return -1; 
	if (Init("GAME1007_SDL_Setup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instance()
{
	static Engine instance; // C++11 will prevent this line from running more than once. Magic statics.
	return instance;
}

SDL_Renderer* Engine::GetRenderer() { return m_pRenderer; }

FSM& Engine::GetFSM() { return *m_pFSM; }

SDL_Point& Engine::GetMousePos() { return m_MousePos; }

bool Engine::GetMouseState(int idx) { return m_MouseState[idx]; }

void Engine::QuitGame() { m_bRunning = false; }
//int Engine::GetMouseX() { return m_iMouseX; }
//int Engine::GetMouseY() { return m_iMouseY; }
//bool Engine::GetMouseBtn(int i) { return m_bMouseBtn[i]; }