#include "Box.h"
#include "Engine.h"
#include <cstdlib>
#include <iostream>

void Box::Update()
{
	int mx = Engine::Instance().GetMousePos().x;
	int my = Engine::Instance().GetMousePos().y;
	if (mx < (m_rDst.x + m_rDst.w) && mx > m_rDst.x && // If cursor is within X bounds
		my < (m_rDst.y + m_rDst.h) && my > m_rDst.y)   // And cursor is within Y bounds
	{
		if (Engine::Instance().GetMouseState(0))
		{
			m_rDst.x = mx - m_rDst.w/2;
			m_rDst.y = my - m_rDst.h/2;
		}
		if (Engine::Instance().GetMouseState(2)) // What can we do to "slow down" the color set?
		{
			m_cColor.r = rand() % 256;
			m_cColor.g = rand() % 256;
			m_cColor.b = rand() % 256;
		}
	}
}

void Box::Render()
{
	std::cout << "box from render with color("<< unsigned( m_cColor.r) <<","<< unsigned( m_cColor.g)<<","<< unsigned( m_cColor.b)<<") and position ("<< m_rDst .x<<","<< m_rDst .y<<")"<< std::endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), m_cColor.r, m_cColor.g, m_cColor.b, m_cColor.a);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &m_rDst);
}
SDL_Rect  Box::getBoxSize()
{
	return m_rDst;
}

SDL_Color Box::getBoxColor()
{
	return m_cColor;
}