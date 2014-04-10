#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "..\..\Engine\Advanced2D.h"

class GameManager
{
public:
	enum GAMESTATE {
		MAIN_MENU, 
		GAME_PLAY, 
		PAUSE, 
		SCORING, 
		GAME_OVER,
		GAME_STATE_MAX
	};
	enum CURRENTPLAYER {
		PLAYER_ONE = 1, 
		PLAYER_TWO = 2, 
		PLAYER_THREE = 3, 
		PLAYER_FOUR = 4, 
		PLAYERS_MAX
	};
private:
	// Store game state
	GAMESTATE gameState;
	// Stores current player for shot purposes
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

	GAMESTATE GetGameState() { return gameState; }
	void SetGameState(GAMESTATE _newState) { gameState = _newState; }

	CURRENTPLAYER GetCurrentPlayer() { return currentPlayer; }
	void SetGameState(CURRENTPLAYER _newPlayer) { currentPlayer = _newPlayer; }

	void ChangePlayer(DWORD _time);
	void AddPlayer();
	void RemovePlayer();
};

#endif

