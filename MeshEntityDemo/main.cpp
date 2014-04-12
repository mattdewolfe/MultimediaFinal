#include "..\Engine\Advanced2D.h"
#include "GameManager.h"
#include "InputController.h"

using namespace Advanced2D;

//camera object
Camera *camera1;
Camera *camera2;
Light *light;
Light *light2;
GameManager *gameManager;
// Input controllers for each player
InputController* inputs[GameManager::PLAYERS_MAX];
void ToggleCamera();
int updateDelay = 0;

bool game_preload() 
{
    g_engine->setAppTitle("Planar");
    g_engine->setFullscreen(false);
    g_engine->setScreenWidth(1600);
    g_engine->setScreenHeight(900);
    g_engine->setColorDepth(32);    
    return 1;
}

bool game_init(HWND) 
{
    //set the camera and perspective
    camera1 = new Camera();
    camera1->setPosition(150.0f, 200.0f, -70.0f);
    camera1->setTarget(0.0f, 0.0f, -15.0f);
    camera1->Update();
	camera2 = new Camera();
    camera2->setPosition(0.0f, 30.0f, -200.0f);
    camera2->setTarget(0.0f, 0.0f, 0.0f);
    camera2->Update();

    //create a directional light
    D3DXVECTOR3 pos(30.0f,0.0f,80.0f);
    D3DXVECTOR3 dir(0.0f,0.0f,80.0f);
    light = new Light(0, D3DLIGHT_POINT, pos, dir, 500);
    light->setColor(D3DXCOLOR(255,0,0,0));
	
	//create a directional light
    D3DXVECTOR3 pos2(30.0f,0.0f,-80.0f);
    D3DXVECTOR3 dir2(0.0f,0.0f,-80.0f);
    light2 = new Light(0, D3DLIGHT_POINT, pos2, dir2, 500);
    light2->setColor(D3DXCOLOR(0,255,0,0));

//    g_engine->SetAmbient(D3DCOLOR_RGBA(255,255,255,0));
	
	// Setup custom classes
	gameManager = new GameManager();
	for (int i = 0; i < GameManager::PLAYERS_MAX; i++)
	{
		inputs[i] = new InputController(DIK_W, DIK_S, DIK_SPACE);
	}
   
    return 1;
}

void game_update() 
{
	if (updateDelay%50 == 0)
	{
		gameManager->Update();
		if(inputs[gameManager->GetCurrentPlayer()]->CheckFire() == true && 
			gameManager->GetGameState() == GAME_PLAY)
		{
			// fire shot
			inputs[gameManager->GetCurrentPlayer()]->SetFireFalse();
			gameManager->FireShot();
		}
	}
	updateDelay++;
	if (updateDelay > 51)
		updateDelay = 0;
}

void game_keyRelease(int key) 
{
	if (key == DIK_T)
	{
		ToggleCamera();
	}
	else if (key == DIK_ESCAPE)
	{
		g_engine->Close();
	}
	else if (key == DIK_RETURN)
	{
		if (gameManager->GetGameState() == Advanced2D::MAIN_MENU)
		{
			gameManager->SetGameState(Advanced2D::GAME_PLAY);
			gameManager->SetupShot();
		}
		else if (gameManager->GetGameState() == Advanced2D::GAME_PLAY)
		{
			gameManager->SetGameState(Advanced2D::PAUSE);
		}
		else if (gameManager->GetGameState() == Advanced2D::PAUSE)
		{
			gameManager->SetGameState(Advanced2D::GAME_PLAY);
		}
		else if (gameManager->GetGameState() == Advanced2D::GAME_OVER)
		{
			gameManager->SetGameState(Advanced2D::MAIN_MENU);
		}
	}

	inputs[(int)gameManager->GetCurrentPlayer()]->ButtonRelease(key);
}

void game_keyPress(int key) 
{
	inputs[gameManager->GetCurrentPlayer()]->ButtonPress(key);
}

void game_entityUpdate(Advanced2D::Entity* entity) 
{ 
    if (entity->getRenderType() == RENDER3D)
    {
        //type-cast Entity to a Mesh
        Mesh* mesh = (Mesh*)entity;

	/*	D3DXVECTOR3 pos = mesh->GetPosition();
		pos.z -= 0.1f;
		mesh->SetPosition(pos);*/
    }
}

void game_entityRender(Advanced2D::Entity* entity) 
{ 
    //type-cast Entity to a Mesh
    Mesh* mesh = (Mesh*)entity;

    //engine automatically renders each entity
    //but we can respond to each render event here
}

void game_end() 
{
    delete camera1;
	delete camera2;
    delete light;
}

void ToggleCamera()
{
	if (gameManager->cameraOne == true)
	{
		gameManager->cameraOne = false;
		camera2->Update();
	}
	else 
	{
		gameManager->cameraOne = true;
		camera1->Update();
	}
}

void game_render3d()
{
    g_engine->ClearScene(D3DCOLOR_RGBA(150,150,150,0));
    g_engine->SetIdentity();
}
void game_render2d() {}
void game_mouseButton(int button) {}
void game_mouseMotion(int x,int y) {}
void game_mouseMove(int x,int y) {}
void game_mouseWheel(int wheel) {}
void game_controllerButtonPressed(int index, int button){}
void game_controllerButtonReleased(int index, int button){}
void game_controllerButtonDown(int index, int button){}
void game_controllerLeftTrigger(int index, int value){}
void game_controllerRightTrigger(int index, int value){}
void game_controllerThumbLX(int index, float value){}
void game_controllerThumbLY(int index, float value){}
void game_controllerThumbRX(int index, float value) {}
void game_controllerThumbRY(int index, float value) {}