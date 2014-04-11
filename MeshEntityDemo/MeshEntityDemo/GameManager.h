#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "..\..\Engine\Advanced2D.h"
#include "GamePlayStates.h"

class GameManager : public virtual GamePlayStates
{
public:
	// Enum for the player who is throwing
	enum CURRENTPLAYER {
		PLAYER_ONE = 1, 
		PLAYER_TWO = 2, 
		PLAYER_THREE = 3, 
		PLAYER_FOUR = 4, 
		PLAYERS_MAX
	};
private:
	// Stores game state
	GAMESTATE gameState;
	// Stores current player
	CURRENTPLAYER currentPlayer;
	// Determines how long player have to make their shot (ms)
	DWORD timePerTurn;
	// Hold start time for current players turn (ms)
	DWORD turnStartTime;
	// How many players are in the game
	int players;

public:
	GameManager(void);
	virtual ~GameManager(void);
	void Update(UINT _val);
	
	void SetTimePerTurn(DWORD _time) { timePerTurn = _time; }
	DWORD GetTimePerTurn() { return timePerTurn; }

	void SetGameState(GAMESTATE _newState) { gameState = _newState; }
	GAMESTATE GetGameState() { return gameState; }

	void ChangePlayer(DWORD _time);
	void AddPlayer();
	void RemovePlayer();
};

#endif

