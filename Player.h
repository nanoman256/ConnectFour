#pragma once
class Player
{
public:
	Player()
	{
	};
	
	const inline int getWins()
	{
		return wins;
	}

	const inline bool isTurn() 
	{
		return isPlayerTurn;
	}

	inline void addWin()
	{
		wins++;
	}
	inline void resetWins()
	{
		wins = 0;
	}

	inline void toggleTurn()
	{
		isPlayerTurn = !isPlayerTurn;
	}
private:
	int wins = 0;
	bool isPlayerTurn = false;
};

