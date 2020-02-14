#pragma once
#include <functional>
#include "SDL.h"

class Button
{
private:
	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state; // Note the new syntax and missing m_iFrame.
	//int m_iFrame;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;
	
	std::function<void()> m_callback; // The button callback!
	bool MouseCollision();
	virtual void Execute() = 0; // Pure virtual method, meaning Button is now an abstract class (interface)!
public:
	Button(const char* s, SDL_Rect src, SDL_Rect dst); //, std::function<void()> cb
	~Button();
	
	void Update();
	void Render();
};
class PlayButton : public Button
{
private:
	void Execute();
public:
	PlayButton(const char* s, SDL_Rect src, SDL_Rect dst);
};

class ExitButton : public Button
{
private:
	void Execute();
public:
	ExitButton(const char* s, SDL_Rect src, SDL_Rect dst);
};

class ResumeButton : public Button
{
private:
	void Execute();
public:
	ResumeButton(const char* s, SDL_Rect src, SDL_Rect dst);
};