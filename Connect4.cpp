#include "Connect4.h"
#include <iostream>
#include <string>

Connect4::Connect4()
{
	window = std::make_unique<Window>("Connect 4", screenWidth, screenHeight);
	m_renderer = SDL_CreateRenderer(window->get(), NULL);
	mouse = std::make_shared<Mouse>();
	player1 = std::make_shared<Player>();
	player2 = std::make_shared<Player>();
	game = std::make_unique<Game>(m_renderer, mouse, player1, player2);
	gameOver = std::make_unique<GameOver>(m_renderer, mouse, player1, player2);
	
	player1->toggleTurn();//start player 1 as first TODO randomize this
	currentState = std::make_unique<Game>(m_renderer, mouse, player1, player2);
}

void Connect4::ChangeState(GameState requestedState) 
{
	currentState->OnClose();
	switch (requestedState)
	{
	case (GameState::Game):
		currentState = std::make_unique<Game>(m_renderer, mouse, player1, player2);
		break;
	case (GameState::GameOver):
		currentState = std::make_unique<GameOver>(m_renderer, mouse, player1, player2);
		break;
	case (GameState::Exit):
		std::exit(0);
	}
	nextGameState = requestedState;
	currentState->OnStart();
}

void Connect4::GameLoop() 
{
	while (true)
	{
		currentState->HandleInput();
		currentState->Update();
		currentState->Render();

		GameState requestedState = currentState->GetNextGameState();
		if (requestedState != nextGameState) 
		{
			ChangeState(requestedState);
		}
	}
}