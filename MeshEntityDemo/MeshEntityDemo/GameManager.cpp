#include "GameManager.h"

GameManager::GameManager(void) :
	timePerTurn(4000),
	roundDelay(1000),
	players(2), 
	gameState(Advanced2D::MAIN_MENU),
	currentShot(1),
	shotsPerTeam(3), 
	shotsPerGame(9), 
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
	if (currentPlayer == PLAYER_ONE)
		currentPlayer = PLAYER_TWO;
	else if (currentPlayer == PLAYER_TWO)
	{
		currentPlayer = PLAYER_ONE;
		currentShot++;
	}

	turnStartTime = clock.getTimer();

	if (currentShot * shotsPerTeam <= shotsPerGame)
		SetupShot();
}

void GameManager::Update()
{
	switch (gameState)
	{
		case Advanced2D::NEXT_SHOT:
			if (turnStartTime + roundDelay < clock.getTimer())
			{
				turnStartTime = clock.getTimer();
				gameState = Advanced2D::GAME_PLAY;
			}
			break;
		case Advanced2D::GAME_PLAY:
			if (turnStartTime + timePerTurn	< clock.getTimer())
			{
				FireShot();
			}
			// if this happens, game be over
			if (currentShot * shotsPerTeam > shotsPerGame)
			{
				// done and done, say who the winner is and stuff
				gameState = Advanced2D::GAME_OVER;
			}
			break;
		case Advanced2D::GAME_OVER:
			// calc winner
			break;
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
			mesh->setAwake(true);
			mesh->SetScale(1.0f,1.0f,1.0f);
			mesh->SetRotation(180, 0, 0);
		
			if (i == 0)
				mesh->setName("team1");
			else if (i == 1)
				mesh->setName("team2");
			else if (i == 2)
				mesh->setName("team3");
			else if (i == 3)
				mesh->setName("team4");

			float x = -40 + i*80;
			float y = 35 + j*5;
			float z = -80;
			mesh->SetPosition(x, y, z);
			// add object to local entity list
			rocks[i][j] = mesh;
			// add mesh to entity manager
			g_engine->addEntity(mesh);
		}
	}
	// need colliders
	Advanced2D::Mesh *terrain;
	// ground plane
	terrain = new Advanced2D::Mesh();
	terrain->setName("ground");
	terrain->CreateCube(350, 5, 350);
	terrain->SetPosition(0, -12, 5);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// target at the end of the board
	terrain = new Advanced2D::Mesh();
	terrain->setName("target");
	terrain->CreateSphere(4, 20, 20);
	terrain->SetPosition(0, -10, 80);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// play board
	terrain = new Advanced2D::Mesh();
	terrain->Load("ball.x");
	terrain->setName("board");
	terrain->CreateCube(40.0f, 2.0f, 200.0f);
	terrain->SetPosition(0, -10, 0);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// left bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(2.0f, 5.0f, 200.0f);
	terrain->SetPosition(-20, -8, 0);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// right bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(2.0f, 5.0f, 200.0f);
	terrain->SetPosition(20, -8, 0);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// rear bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(20.0f, 5.0f, 5.0f);
	terrain->SetPosition(0, -8, 100);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// front bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(40.0f, 5.0f, 5.0f);
	terrain->SetPosition(0, -8, -100);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	// middle bumbper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(10.0f, 10.0f, 5.0f);
	terrain->SetPosition(0, -8, 0);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
}

void GameManager::FireShot()
{
	rocks[currentPlayer][currentShot - 1]->SetVelocity(0.0f, 0.0f, 0.01f);
	gameState = Advanced2D::NEXT_SHOT;
	ChangePlayer();
	turnStartTime = clock.getTimer();
}

void GameManager::Reset()
{
	players = 2; 
	gameState = Advanced2D::MAIN_MENU;
	currentShot = 1;
	cameraOne = false;
	currentPlayer = PLAYER_ONE;
}

void GameManager::SetupShot()
{
	rocks[currentPlayer][currentShot - 1]->SetPosition(0.0f, -6.0f, -85.0f);
}

GameManager::~GameManager(void)
{
}
