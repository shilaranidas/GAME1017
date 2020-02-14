#include <functional>
#include <iostream>
#include "FSM.h"
#include "Engine.h"
#include <ctime>
using namespace std;

// Begin State. CTRL+M+H and CTRL+M+U to turn on/off collapsed code.
void State::Render()
{
	//cout << "Rendering State..."  << endl;
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
void State::Resume() {
	//cout << "Resume State..."  << endl;
}
// End State.

// Begin PauseState.
PauseState::PauseState() {}

void PauseState::Enter()
{
	//cout << "Entering Pause..." << endl;
	m_vButtons.push_back(new ResumeButton("Img/resume.png", { 0,0,200,80 }, { 412,200,200,80 }));
	//,	std::bind(&FSM::PopState, &Engine::Instance().GetFSM())
	// This exit button has a different size but SAME function as the one in title.
	m_vButtons.push_back(new ExitButton("Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }) );
	//,	std::bind(&Engine::QuitGame, &Engine::Instance())
}

void PauseState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
}

void PauseState::Render()
{
	//cout << "Rendering PauseState..."  << endl;
	Engine::Instance().GetFSM().GetStates().front()->Render();
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void PauseState::Exit()
{
	//cout << "Exiting Pause..." << endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
// End PauseState.

// Begin GameState.
GameState::GameState() {}

void GameState::Enter()
{ 
	//cout << "Entering Game..." << endl;
	srand((unsigned)time(NULL));
	Engine::Instance(). m_vBoxes.reserve(4);
	DataHandle* dh = new DataHandle();
	Engine::Instance().m_vBoxes =dh->ReadData();
	delete dh;
	/*m_vBoxes.push_back(new Box({ 100, 100, 100, 100 }));
	m_vBoxes.push_back(new Box({ 800, 100, 100, 100 }));
	m_vBoxes.push_back(new Box({ 100, 500, 100, 100 }));
	m_vBoxes.push_back(new Box({ 800, 500, 100, 100 }));*/
}

void GameState::Update()
{
	for (int i = 0; i < (int)Engine::Instance().m_vBoxes.size(); i++)
		Engine::Instance().m_vBoxes[i]->Update();
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P) == 1)
		Engine::Instance().GetFSM().PushState(new PauseState());
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_X) == 1)
		Engine::Instance().GetFSM().ChangeState(new TitleState());
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_SPACE) == 1)
	{
		for (int i = 0; i < (int)Engine::Instance().m_vBoxes.size(); i++)
			Engine::Instance().m_vBoxes[i]->Reset();
	}

}

void GameState::Render()
{
	//cout << "Rendering GameState..."<< Engine::Instance().m_vBoxes.size() << endl;
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Render stuff.
	for (int i = 0; i < (int)Engine::Instance().m_vBoxes.size(); i++)
		Engine::Instance().m_vBoxes[i]->Render();
	// If GameState != current state.
	if (dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void GameState::Exit()
{ 
	//cout << "Exiting Game..." << endl;
	DataHandle* dh = new DataHandle();
	dh->WriteData(Engine::Instance().m_vBoxes);
	delete dh;
	for (int i = 0; i < (int)Engine::Instance().m_vBoxes.size(); i++)
	{
		delete Engine::Instance().m_vBoxes[i];
		Engine::Instance().m_vBoxes[i] = nullptr;
	}
	Engine::Instance().m_vBoxes.clear();
}

void GameState::Resume()
{
	//cout << "Resuming GameState ..." << Engine::Instance().m_vBoxes.size() << endl;
//	DataHandle* dh = new DataHandle();
	//m_vBoxes = dh->ReadData();

	//delete dh;
}

// End GameState.

// Begin TitleState.
TitleState::TitleState() {}

void TitleState::Enter()
{ 
	//cout << "Entering Title..." << endl;
	m_vButtons.push_back(new PlayButton("Img/button.png", { 0,0,400,100 }, { 312,100,400,100 }));
	//,	std::bind(&FSM::ChangeState, &Engine::Instance().GetFSM(), new GameState())
	// For the bind: what function, what instance, any parameters.
	m_vButtons.push_back(new ExitButton("Img/exit.png", { 0,0,400,100 }, { 312,300,400,100 }));
	//,	std::bind(&Engine::QuitGame, &Engine::Instance())
}

void TitleState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
}

void TitleState::Render()
{
	//cout << "Rendering Title..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void TitleState::Exit()
{ 
	//cout << "Exiting Title..." << endl;
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
// End TitleState.

// Begin StateMachine.

void FSM::Update()
{
	if (!m_vStates.empty()) // empty() and back() are methods of the vector type.
		m_vStates.back()->Update();
}

void FSM::Render()
{
	if (!m_vStates.empty())
		m_vStates.back()->Render();
}

void FSM::ChangeState(State* pState)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();	// De-allocating the state in the heap.
		m_vStates.back() = nullptr; // Nullifying pointer to the de-allocated state.
		m_vStates.pop_back();		// Removes the now-null pointer from the vector.
	}
	PushState(pState); // Invokes method below.
}

void FSM::PushState(State* pState)
{
	m_vStates.push_back(pState);
	m_vStates.back()->Enter();
}

void FSM::PopState()
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void FSM::Clean()
{
	while (!m_vStates.empty()) // Because we can exit the game in the pause state with the window's 'X'.
	{						   // Ensures that ALL states left in the vector are cleaned up.
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

vector<State*>& FSM::GetStates() { return m_vStates; }
// End StateMachine.

//ostream & operator<<(ostream & os, const FSM & e)
//{
//	// TODO: insert return statement here
//	//os << e.GetStates(). << ": " << e.health << "|" << e.speed;
//	return NULL;
//}
