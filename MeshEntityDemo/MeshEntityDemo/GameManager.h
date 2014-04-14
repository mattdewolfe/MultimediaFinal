#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "..\..\Engine\Advanced2D.h"
#include "InputController.h"
#include "Menu.h"
#include "HUD.h"

class GameManager
{
public:
	// Enum for the player who is throwing
	enum CURRENTPLAYER {
		PLAYER_ONE = 0, 
		PLAYER_TWO = 1, 
		PLAYERS_MAX = 2
	};
	bool cameraOne;
	float autoShotAngle;
private:
	// Game state - Do not change with =, only with SetGameState function
	// otherwise sprite drawStates will not be checked
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
	int currentShot, shotsPerTeam, shotsPerGame, roundDelay,  powerIncrementalTimer;
	// Timer
	Advanced2D::Timer clock;
	// hud class
	HUD* hud;
	Menu* mainMenu;
	Menu* pauseMenu;
	// Local list of entities for team rocks
	Advanced2D::Mesh* rocks[PLAYERS_MAX][4]; 
	// copy of input pointers stored here for reference
	InputController* inputs[PLAYERS_MAX];

public:
	GameManager();
	void drawMenu();
	void drawHUD();
	void UpdateVisuals(Advanced2D::GAMESTATE _perState);
	virtual ~GameManager(void);

#pragma region Get/Set
	
	void SetTimePerTurn(DWORD _time) { timePerTurn = _time; }
	DWORD GetTimePerTurn() { return timePerTurn; }

	void SetGameState(Advanced2D::GAMESTATE _newState) 
	{ 
		gameState = _newState; 
		UpdateVisuals(gameState);
	}
	Advanced2D::GAMESTATE GetGameState() { return gameState; }

	void SetTotalShots(int _shots)
	{ 
		shotsPerTeam = _shots; 
		shotsPerGame = shotsPerTeam * players;
	}
	int GetTotalShots() { return shotsPerTeam; }

	int GetCurrentPlayer() { return (int)currentPlayer; }

#pragma endregion Get/Set	

	// Switch to next player to shoot
	void ChangePlayer();
	/* Update function for game manager
	** Checks time remaining to shoot, and force fire if expired
	** Checks if all shots have been taken
	*/ 
	void Update();
	// load in meshes
	void InitObjects();
	// fire the current object, with parameters from input
	void FireShot(float _angle, float _power);
	// reset all game elements
	void Reset();
	// setup next shot by moving object into position
	void SetupShot();
	// pass input from main loop into manager
	void PassKeyPressInput(int _key);
	void PassKeyReleaseInput(int _key);
};

#endif

