#include "GameManager.h"

GameManager::GameManager(void) :
	timePerTurn(4000),
	players(2), 
	gameState(Advanced2D::MAIN_MENU),
	currentShot(1),
	shotsPerTeam(4), 
	shotsPerGame(8)
{
	ui = new UI();
	ui->LoadSprites();
	ui->UpdateVisuals(gameState);
}

void GameManager::ChangePlayer()
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

	turnStartTime = clock.getTimer();
}

void GameManager::AddPlayer(void)
{
	if (players < PLAYERS_MAX)
	{
		players++;
		shotsPerGame = shotsPerTeam * players;
	}
}
void GameManager::RemovePlayer(void)
{
	if (players > 2)
	{
		players--;
		shotsPerGame = shotsPerTeam * players;
	}
}

void GameManager::Update()
{
	// if time is up, force the shot and change player
	if (turnStartTime + timePerTurn	< clock.getTimer())
	{
		// force shot now
		ChangePlayer();
	}
	// if this happens, game be over
	else if (currentShot > shotsPerGame)
	{
		// done and done, say who the winner is and stuff
		gameState = Advanced2D::GAME_OVER;
	}

}

GameManager::~GameManager(void)
{
}
