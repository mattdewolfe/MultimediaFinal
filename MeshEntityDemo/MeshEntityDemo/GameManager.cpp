#include "GameManager.h"

GameManager::GameManager() :
	timePerTurn(5000),
	powerIncrementalTimer(0),
	roundDelay(1000),
	players(2), 
	gameState(Advanced2D::MAIN_MENU),
	currentShot(1),
	shotsPerTeam(3), 
	shotsPerGame(9), 
	cameraOne(false),
	currentPlayer(PLAYER_ONE), 
	winningPlayer(PLAYERS_MAX),
	autoShotAngle(0), 
	currentRound(0)
{
	// init the hud
	hud = new HUD();

	// Setup input controllers
	for (int i = 0; i < GameManager::PLAYERS_MAX; i++)
	{
		inputs[i] = new InputController();
		scores[0][i] = 0;
		scores[1][i] = 0;
		scores[2][i] = 0;
		scores[3][i] = 0;
	}
	physicsManager = new PhysicsManager();

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

void GameManager::UpdateVisuals(Advanced2D::GAMESTATE _perState)
{
	//get list of all entities
	std::list<Advanced2D::Entity*> sprites = g_engine->getEntityList();

	std::list<Advanced2D::Entity*>::iterator iter;
	iter = sprites.begin();
	Advanced2D::Entity* currentEntity;
	while (iter != sprites.end())
	{
		currentEntity = *iter;
		if (currentEntity->getRenderType() == Advanced2D::RENDER2D)
		{
			if (currentEntity->getDrawState() == _perState)
			{
				currentEntity->setVisible(true);
			}
			else { currentEntity->setVisible(false); }
		}
		iter++;
	}
}

void GameManager::Update()
{
	switch (gameState)
	{
		case Advanced2D::NEXT_SHOT:
			if (turnStartTime + roundDelay < clock.getTimer())
			{
				turnStartTime = clock.getTimer();
				SetGameState(Advanced2D::GAME_PLAY);
			}
			
			if (physicsManager->AwardPlayerOnePoints() == true)
				AwardPoints(PLAYER_ONE);
			else if (physicsManager->AwardPlayerTwoPoints() == true)
				AwardPoints(PLAYER_TWO);

			physicsManager->Update();
			break;
		case Advanced2D::GAME_PLAY:
			if (inputs[currentPlayer]->CheckFire() == true)
			{
				inputs[currentPlayer]->SetFireFalse();
				FireShot(inputs[currentPlayer]->GetShotAngle(), inputs[currentPlayer]->GetShotPower());
			}
			else if (turnStartTime + timePerTurn < clock.getTimer())
			{
				FireShot(inputs[currentPlayer]->GetShotAngle(), inputs[currentPlayer]->GetShotPower());
			}
			// if this happens, game be over
			if (currentShot * shotsPerTeam > shotsPerGame)
			{
				currentRound++;
				if (currentRound >= ROUNDSPERGAME)
				{
					// done and done, say who the winner is and stuff
					SetGameState(Advanced2D::GAME_OVER);
					winningPlayer = CalculateWinner();
				}
				else
				{
					SetGameState(Advanced2D::ROUND_OVER);
					turnStartTime = clock.getTimer();
				}
			}
			//increase power of shot every half a second
			if (powerIncrementalTimer + 500 < clock.getTimer())
			{
				inputs[currentPlayer]->incrementShotPower();
				powerIncrementalTimer = clock.getTimer();
			}
			
			if (physicsManager->AwardPlayerOnePoints() == true)
				AwardPoints(PLAYER_ONE);
			else if (physicsManager->AwardPlayerTwoPoints() == true)
				AwardPoints(PLAYER_TWO);
			
			physicsManager->Update();
			break;

		case Advanced2D::ROUND_OVER:
			if (turnStartTime + timePerTurn < clock.getTimer())
			{
				// reset objects for next round
				SetupNextRound();
				SetGameState(Advanced2D::GAME_PLAY);
				turnStartTime = clock.getTimer();
				// update scoreboard
			}
			if (physicsManager->AwardPlayerOnePoints() == true)
				AwardPoints(PLAYER_ONE);
			else if (physicsManager->AwardPlayerTwoPoints() == true)
				AwardPoints(PLAYER_TWO);

			physicsManager->Update();

		case Advanced2D::GAME_OVER:
			// draw messaage for winning team
			break;
		case Advanced2D::EXITING:
			g_engine->Close();
			break;
	}
}

void GameManager::InitObjects()
{
	inputs[1]->SetAngleDownBtn(DIK_LEFTARROW);
	inputs[1]->SetAngleUpBtn(DIK_RIGHTARROW);
	inputs[1]->SetShootBtn(DIK_L);
	
	Advanced2D::Mesh *mesh;
	for (int i = 0; i < players; i++)
	{
		for (int j = 0; j < shotsPerTeam; j++)
		{
			mesh = new Advanced2D::Mesh();
			if (i == 0)
			{
				mesh->Load("airplane 2.x");
				mesh->setAwake(true);
				mesh->SetScale(1.0f,1.0f,1.0f);
				mesh->SetRotation(180, 0, 0);
				mesh->setName("team1");
			}
			else if (i == 1)
			{
				mesh->Load("airplane 2.x");
				mesh->setAwake(true);
				mesh->SetScale(1.0f,1.0f,1.0f);
				mesh->SetRotation(180, 0, 0);
				mesh->setName("team2");
			}
			float x = -40 + i*80;
			float y = 35 + j*5;
			float z = -80;
			mesh->SetPosition(x, y, z);
			mesh->startPosition = D3DXVECTOR3(x, y, z);
			// add collider and push to physics 
			mesh->AddSphereCollider(1.5);
			physicsManager->AddPhysicsBody(mesh);
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
	terrain->AddAABBCollider(350,5,250);	
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);

	// target at the end of the board
	terrain = new Advanced2D::Mesh();
	terrain->setName("target");
	terrain->CreateSphere(4, 20, 20);
	terrain->SetPosition(0, -10, 80);
	terrain->AddAABBCollider(4,20,4);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);

	// play board
	terrain = new Advanced2D::Mesh();
	terrain->Load("ball.x");
	terrain->setName("board");
	terrain->CreateCube(40.0f, 2.0f, 200.0f);
	terrain->SetPosition(0, -10, 0);
	terrain->AddAABBCollider(40, 2, 200);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);

	// left bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(2.0f, 5.0f, 200.0f);
	terrain->SetPosition(-20, -8, 0);
	terrain->AddAABBCollider(2, 5, 200);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);

	// right bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(2.0f, 5.0f, 200.0f);
	terrain->SetPosition(20, -8, 0);
	terrain->AddAABBCollider(2, 5, 200);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	
	// rear bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(20.0f, 5.0f, 5.0f);
	terrain->SetPosition(0, -8, 100);
	terrain->AddAABBCollider(20, 5, 5);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);

	// front bumper
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(40.0f, 5.0f, 5.0f);
	terrain->SetPosition(0, -8, -100);
	terrain->AddAABBCollider(40, 5, 5);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);
	
	// mid-map obstacle
	terrain = new Advanced2D::Mesh();
	terrain->setName("bumper");
	terrain->CreateCube(10.0f, 10.0f, 5.0f);
	terrain->SetPosition(0, -8, 0);
	terrain->AddAABBCollider(10, 10, 5);
	physicsManager->AddPhysicsBody(terrain);
	terrain->setAwake(true);
	g_engine->addEntity(terrain);

	// hud elements (2d)

	Advanced2D::Sprite *sprite = new Advanced2D::Sprite();
	sprite->loadImage("main_menu.png");
	mainMenu = new Menu(sprite);
	mainMenu->addItem("START", Advanced2D::GAME_PLAY);
	mainMenu->addItem("HELP", Advanced2D::HELP);
	mainMenu->addItem("EXIT", Advanced2D::EXITING);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("pause.png");
	pauseMenu = new Menu(sprite);
	pauseMenu->addItem("RESUME", Advanced2D::GAME_PLAY);
	pauseMenu->addItem("EXIT", Advanced2D::EXITING);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("help_screen.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::HELP);
	g_engine->addEntity(sprite);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("exit.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::EXITING);
	g_engine->addEntity(sprite);

	//set 2D visuals for the current gamestate
	UpdateVisuals(gameState);
}

void GameManager::FireShot(float _angle, float _power)
{
	// calc shot angle from input controller
	float x = _angle;
	float z = _power;
	// calculate z and x values based on power/angle
	rocks[currentPlayer][currentShot - 1]->SetVelocity(x, 0.0f, z);
	SetGameState(Advanced2D::NEXT_SHOT);
	ChangePlayer();
	turnStartTime = clock.getTimer();
}

void GameManager::Reset()
{
	players = 2; 
	SetGameState(Advanced2D::MAIN_MENU);
	currentShot = 1;
	cameraOne = false;
	currentPlayer = PLAYER_ONE;
	currentRound = 0;
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		scores[0][i] = 0;
		scores[1][i] = 0;
		scores[2][i] = 0;
		scores[3][i] = 0;
	}
}

void GameManager::SetupShot()
{
	rocks[currentPlayer][currentShot - 1]->SetPosition(0.0f, -6.0f, -85.0f);
	turnStartTime = clock.getTimer();
}

void GameManager::PassKeyPressInput(int _key)
{
	// only the input controller should be watching for key down
	inputs[currentPlayer]->ButtonPress(_key, gameState);
}

void GameManager::PassKeyReleaseInput(int _key)
{
	// if escape is pressed, the game closes
	if (_key == DIK_ESCAPE)
	{
		g_engine->Close();
	}
	// if enter is pressed, check state and proceed to next gameplay state
	// or pause/unpause the game
	if (_key == DIK_RETURN)
	{
		if (gameState == Advanced2D::MAIN_MENU)
		{
			SetGameState(mainMenu->getMenuItem(mainMenu->getCurrentSelection())->getGoToState());
			if (gameState == Advanced2D::GAME_PLAY) { SetupShot(); }
		}
		else if (gameState == Advanced2D::GAME_PLAY)
		{
			SetGameState(Advanced2D::PAUSE);
		}
		else if (gameState == Advanced2D::PAUSE)
		{
			SetGameState(pauseMenu->getMenuItem(pauseMenu->getCurrentSelection())->getGoToState());
		}
		else if (gameState == Advanced2D::HELP)
		{
			SetGameState(Advanced2D::MAIN_MENU);
		}
		else if (gameState == Advanced2D::GAME_OVER)
		{
			Reset();
		}
	}
	else
	{
		// otherwise pass input onto current controller for menus
		if (gameState == Advanced2D::MAIN_MENU)
		{
			inputs[PLAYER_ONE]->ButtonRelease(_key, gameState, mainMenu);
			inputs[PLAYER_TWO]->ButtonRelease(_key, gameState, mainMenu);
		}
		else if (gameState == Advanced2D::PAUSE)
		{
			inputs[PLAYER_ONE]->ButtonRelease(_key, gameState, pauseMenu);
			inputs[PLAYER_TWO]->ButtonRelease(_key, gameState, pauseMenu);
		}
	}
}

void GameManager::drawMenu()
{
	switch (gameState)
	{
	case Advanced2D::MAIN_MENU:
		mainMenu->show();
		break;
	case Advanced2D::PAUSE:
		pauseMenu->show();
		break;
	}
}

void GameManager::drawHUD()
{
	if (gameState == Advanced2D::GAME_PLAY)
		hud->show(inputs[currentPlayer]->GetShotAngle(), inputs[currentPlayer]->GetShotPower(), ((timePerTurn + turnStartTime - clock.getTimer()) / 1000) + 1);
}

void GameManager::AwardPoints(int _team)
{
	int points = rand()%5;
	scores[currentRound][_team] += points;
}

void GameManager::SetupNextRound()
{
	Advanced2D::Entity* currentEntity;
	std::list<Advanced2D::Entity*> temp = g_engine->getEntityList();
	std::list<Advanced2D::Entity*>::iterator iter;
	iter = temp.begin();
	while (iter != temp.end())
    {
		currentEntity = *iter;
		if (currentEntity->getRenderType() == Advanced2D::RENDER3D)
		{
			Advanced2D::Mesh* mesh = dynamic_cast<Advanced2D::Mesh*>(*iter);
			if (mesh->getName() == "team1" || mesh->getName() == "team2")
			{
				//point local sprite to object in the list
				mesh->setAwake(true);
				mesh->setVisible(true);
				mesh->SetPosition(mesh->startPosition);
				mesh->SetRotation(180, 0, 0);
				mesh->SetVelocity(0, 0, 0);
			}
		}
		iter++;
    }
	currentShot = 1;
	SetupShot();
}

GameManager::CURRENTPLAYER GameManager::CalculateWinner()
{
	// First sum all points
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		for (int j = 0; j < ROUNDSPERGAME; j++)
		{
			scores[ROUNDSPERGAME][i] += scores[j][i];
		}
	}
	// Next determine highest
	int winner = 0;
	for (int i = 1; i < PLAYERS_MAX; i++)
	{
		if (scores[ROUNDSPERGAME][i] > scores[ROUNDSPERGAME][winner])
			winner = i;
	}
	
	// Double check that there is no ties
	bool tie = false;
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		if (scores[ROUNDSPERGAME][i] == scores[ROUNDSPERGAME][winner])
			tie = true;
	}
	// if there was no tie, return the winner
	if (tie == false)
		return (CURRENTPLAYER)winner;
	// otherwise return enumerator max to flag a tie
	else
		return PLAYERS_MAX;
}

GameManager::~GameManager(void)
{
}
