#include <SDL3/SDL.h>

#pragma once
const int gridHeight = 6;
const int gridWidth = 8;
const int screenHeight = 600;
const int screenWidth = 800;
const int squareLength = (screenHeight - 100) / gridHeight;
const int squareHeight = (screenWidth - 100) / gridWidth;
const int gridOffsetX = 80;
const int gridOffsetY = 30;
const int winnerX = screenWidth / 4;
const int winnerY = screenHeight / 6;
const int winnerTextWidth = screenWidth / 2;
const int winnerTextHeight = screenHeight / 4;
const int playAgainX = (screenHeight - screenHeight / 10);
const int playAgainY = screenWidth / 2;
const int playAgainWidth = 100;
const int playAgainHeight = 20;

//SDL color constants
const SDL_Color RED = { 255, 0, 0, 255 };
const SDL_Color TRANS_RED = { 255, 0, 0, 155 };
const SDL_Color BLUE = { 0, 0, 255, 255 };
const SDL_Color TRANS_BLUE = { 0, 0, 255, 155 };
const SDL_Color WHITE = { 0xFF, 0xFF, 0xFF, 0xFF };
const SDL_Color BLACK = { 0, 0, 0, 255 };

enum class GameState {
	//Menu,
	Game,
	PauseMenu,
	GameOver,
	Exit
};