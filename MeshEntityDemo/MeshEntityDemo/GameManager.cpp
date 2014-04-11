#include "GameManager.h"

GameManager::GameManager(void) :
	timePerTurn(4000),
	players(2), 
	gameState(Advanced2D::MAIN_MENU),
	currentShot(1),
	shotsPerTeam(4), 
	shotsPerGame(8), 
	cameraOne(false),
	currentPlayer(PLAYER_ONE)
{
	ui = new UI();
	ui->LoadSprites();
	ui->UpdateVisuals(gameState);
	// setup objects for each team
	InitObjects();
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

void GameManager::InitObjects()
{
	Advanced2D::Mesh *mesh;
	for (int i = 0; i < players; i++)
	{
		for (int j = 0; j < shotsPerTeam; j++)
		{
			mesh = new Advanced2D::Mesh();
			mesh->Load("airplane 2.x");
			mesh->SetScale(1.0f,1.0f,1.0f);
			mesh->SetRotation(180, 0, 0);
			mesh->setName("team" + i);
			float x = -15 + j*10;
			float y = 30 + i*4;
			float z = -4;
			mesh->SetPosition(x,y,z);

			//add mesh to entity manager
			g_engine->addEntity(mesh);
		}
	}
	// need colliders
	Advanced2D::Mesh *ice;
	ice = new Advanced2D::Mesh();
	ice->CreateSphere(2, 20, 20);
	ice->SetPosition(0, -10.5, 45);
	g_engine->addEntity(ice);

	ice = new Advanced2D::Mesh();
	ice->CreateCube(250, 5, 250);
	ice->SetPosition(0, -12, 5);
	g_engine->addEntity(ice);

	ice = new Advanced2D::Mesh();
	ice->Load("ball.x");
	ice->CreateCube(25.0f, 2.0f, 116.0f);
	ice->SetPosition(0, -10, 0);
	g_engine->addEntity(ice);

	ice = new Advanced2D::Mesh();
	ice->CreateCube(5.0f, 2.0f, 120.0f);
	ice->SetPosition(-9.3625f, -8, 0);
	g_engine->addEntity(ice);

	ice = new Advanced2D::Mesh();
	ice->CreateCube(5.0f, 2.0f, 120.0f);
	ice->SetPosition(9.3625f, -8, 0);
	g_engine->addEntity(ice);
	
	ice = new Advanced2D::Mesh();
	ice->CreateCube(25.0f, 2.0f, 5.0f);
	ice->SetPosition(0, -8, 57.5);
	g_engine->addEntity(ice);
}

GameManager::~GameManager(void)
{
}
