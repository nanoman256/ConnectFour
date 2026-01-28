#include "constants.h"
#pragma once
class IGameState
{
public:
	virtual ~IGameState() {}

	virtual void OnStart() = 0;
	virtual void OnClose() = 0;

	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void HandleInput() = 0;
	virtual GameState GetNextGameState() = 0;
};

