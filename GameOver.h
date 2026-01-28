#include "constants.h"
#include "TextLabel.h"
#include "Mouse.h"
#include <memory>
#include "IGameState.h"
#include "Player.h"
#pragma once
class GameOver : public IGameState
{
public:
	GameOver(SDL_Renderer* renderer,  std::shared_ptr<Mouse> mouse, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) 
		: m_renderer(renderer),
			m_player1(p1),
			m_player2(p2),
			winner(screenWidth / 4, screenHeight / 4, 200, 100),
			playAgain(screenHeight - screenHeight / 10, screenWidth / 2, 100, 20)
	{
		exitGame = TextLabel();//figure out dimensions
		m_mouse = mouse;
		m_buttonFont = TTF_OpenFont("font.ttf", 24);
		m_font = TTF_OpenFont("font.ttf", 48);
		if (!m_font || !m_buttonFont) 
		{
			SDL_Log("Could not initialize font: %s", SDL_GetError());
		}

		playAgain.SetLabel(m_renderer, m_buttonFont, "Play Again?");
	}
	~GameOver() 
	{
		if (m_font) TTF_CloseFont(m_font);
		if (m_buttonFont) TTF_CloseFont(m_buttonFont);
	}
	void HandleInput();
	void Update();
	void Render();

	//handle input
	void HandleMouseMotion();
	void HandleMouseClick();
	
	//update
	GameState GetNextGameState();
	void SetNextGameState(GameState state);

	//render
	void RenderWinnerScreen();
	void RenderPlayAgainButton();
	//void RenderCloseGameButton();

	void OnStart();
	void OnClose();

	
private:
	GameState nextGameState = GameState::GameOver;
	SDL_Renderer* m_renderer = nullptr;

	TextLabel winner;
	TextLabel playAgain;
	TextLabel exitGame;

	TTF_Font* m_font;
	TTF_Font* m_buttonFont;

	std::shared_ptr<Player> m_player1 = nullptr;
	std::shared_ptr<Player> m_player2 = nullptr;

	//mouse values
	std::shared_ptr<Mouse> m_mouse = nullptr;
	float mouseX = 0;
	float mouseY = 0;
};

