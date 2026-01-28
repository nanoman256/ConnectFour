#include "GameOver.h"
void GameOver::HandleInput() 
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
			SetNextGameState(GameState::Exit);
		if (event.type == SDL_EVENT_MOUSE_MOTION) 
		{
			m_mouse->UpdateMousePos(event.motion.x, event.motion.y);
			HandleMouseMotion();
		}
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			HandleMouseClick();
		}
	}
}

void GameOver::HandleMouseMotion() 
{

}

void GameOver::HandleMouseClick() 
{
	SDL_FPoint point = m_mouse->GetMousePos();
	SDL_FRect rect = playAgain.GetRect();
	if (SDL_PointInRectFloat(&point, &rect)) 
	{
		SetNextGameState(GameState::Game);
	}
}


void GameOver::SetNextGameState(GameState state) 
{
	nextGameState = state;
}

GameState GameOver::GetNextGameState()
{
	return nextGameState;
}

void GameOver::RenderWinnerScreen() 
{
	winner.Draw(m_renderer);
}

void GameOver::RenderPlayAgainButton() 
{
	playAgain.Draw(m_renderer);
}

void GameOver::Update() 
{

}

void GameOver::Render() 
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	RenderWinnerScreen();
	RenderPlayAgainButton();
	SDL_RenderPresent(m_renderer);
}

void GameOver::OnClose() 
{
	return;
}
void GameOver::OnStart() 
{
	return;
}