#include "GameManager.h"

GameManager::GameManager(void) :
	timePerTurn(3000),
	players(2)
{
}

void GameManager::ChangePlayer(DWORD _time)
{
	// Change to next player in order, or back to start
	if (currentPlayer > players)
		currentPlayer = PLAYER_ONE;
	else if (currentPlayer == PLAYER_ONE)
		currentPlayer = PLAYER_TWO;
	else if (currentPlayer == PLAYER_TWO)
		currentPlayer = PLAYER_THREE;
	else if (currentPlayer == PLAYER_THREE)
		currentPlayer = PLAYER_FOUR;

	turnStartTime = _time;		
}

void GameManager::AddPlayer(void)
{
	if (players < PLAYERS_MAX)
		players++;
}
void GameManager::RemovePlayer(void)
{
	if (players > 2)
		players--;
}

GameManager::~GameManager(void)
{
}
