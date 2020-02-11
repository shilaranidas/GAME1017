#pragma once
#include "SDL.h"

class Box
{
private:
	SDL_Rect m_rDst;
	SDL_Rect m_rStartPos;
	SDL_Color m_cColor;
public:
	Box(SDL_Rect r)
	{
		m_rDst = m_rStartPos = r;
		m_cColor = { 255, 255, 255, 255 };
	}
	Box(SDL_Rect r, SDL_Color c)
	{
		m_rDst = m_rStartPos = r;
		m_cColor = c;
	}
	void Update();
	void Render();
	SDL_Rect getBoxSize();
	SDL_Color getBoxColor();
	void Reset() { m_rDst = m_rStartPos; }
};