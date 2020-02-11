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
	void Update();
	void Render();
	void Reset() { m_rDst = m_rStartPos; }
};