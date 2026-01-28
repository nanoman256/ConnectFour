#include <SDL3/SDL.h>
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>
#include "Game.h"
#include "PauseMenu.h"
#include "Window.h"
#include <memory>
#include "GameOver.h"
#include "Player.h"

//#include "Menu.h"
//#include "StartMenu.h"
#pragma once


class Connect4
{
public:
	Connect4();

	void GameLoop();
	void ChangeState(GameState requestedState);

	~Connect4()
	{
		SDL_DestroyRenderer(m_renderer);
	}
private:
	std::unique_ptr<Game> game = nullptr;
	std::unique_ptr<Window> window = nullptr;
	std::unique_ptr<GameOver> gameOver = nullptr;
	std::shared_ptr<Mouse> mouse = nullptr;
	std::shared_ptr<Player> player1 = nullptr;
	std::shared_ptr<Player> player2 = nullptr;
	std::unique_ptr<IGameState> currentState;
	GameState nextGameState = GameState::Game;
	//Pause pause;
	//PauseMenu pauseMenu;
	SDL_Renderer* m_renderer = nullptr;
};