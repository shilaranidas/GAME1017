#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "FSM.h"


// Do not include any macros, initialized properties or full function definitions in this header.

class Engine
{
private: // Private properties.
	bool m_bRunning; // Loop control flag.
	bool m_bColorSet = false;
	//bool m_bMouseBtn[2] = { false, false };
	//int m_iMouseX, m_iMouseY;  // Variables to hold mouse positions. Maybe better as array?
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.
	FSM* m_pFSM; // Pointer to the StateMachine object created dynamically.
	SDL_Point m_MousePos;
	bool m_MouseState[3] = { 0,0,0 }; // Button up/down. Left, Middle, Right.
	
private: // Private methods.
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
public:
	vector<Box*> m_vBoxes;
public: // Public methods.
	Engine();
	~Engine();
	int Run();
	static Engine& Instance(); // This static method creates the static instance that can be accessed 'globally'
	bool KeyDown(SDL_Scancode c);

	SDL_Renderer* GetRenderer();
	FSM& GetFSM();
	SDL_Point& GetMousePos();
	bool GetMouseState(int idx);
	//int GetMouseX();
	//int GetMouseY();
	//bool GetMouseBtn(int i);
	void QuitGame();
};