#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "..\..\Engine\Advanced2D.h"
#include "UI.h"
class GameManager
{
public:
	// Enum for the player who is throwing
	enum CURRENTPLAYER {
		PLAYER_ONE = 1, 
		PLAYER_TWO = 2, 
		PLAYER_THREE = 3, 
		PLAYER_FOUR = 4, 
		PLAYERS_MAX = 5
	};
private:
	// Stores game state
	Advanced2D::GAMESTATE gameState;
	// Stores current player
	CURRENTPLAYER currentPlayer;
	// Determines how long player have to make their shot (ms)
	DWORD timePerTurn;
	// Hold start time for current players turn (ms)
	DWORD turnStartTime;
	// How many players are in the game
	int players;
	// shot tracking vals, store current shot num, shots per team, and total shots per game
	int currentShot, shotsPerTeam, shotsPerGame;
	// Timer
	Advanced2D::Timer clock;
	// 2d sprite visual handler
	UI* ui;

public:
	GameManager(void);
	virtual ~GameManager(void);
	void Update(UINT _val);
#pragma region Get/Set
	void SetTimePerTurn(DWORD _time) { timePerTurn = _time; }
	DWORD GetTimePerTurn() { return timePerTurn; }

	void SetGameState(Advanced2D::GAMESTATE _newState) 
	{ 
		gameState = _newState; 
		ui->UpdateVisuals(gameState);
	}
	Advanced2D::GAMESTATE GetGameState() { return gameState; }

	void SetTotalShots(int _shots)
	{ 
		shotsPerTeam = _shots; 
		shotsPerGame = shotsPerTeam * players;
	}
	int GetTotalShots() { return shotsPerTeam; }
#pragma endregion Get/Set	
	// Switch to next player to shoot
	void ChangePlayer();
	// Add a player, capped to max of enum
	void AddPlayer();
	// Remove a player, minimum 2
	void RemovePlayer();
	/* Update function for game manager
	** Checks time remaining to shoot, and force fire if expired
	** Checks if all shots have been taken
	*/ 
	void Update();
};

#endif

