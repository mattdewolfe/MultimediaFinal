#include "..\Engine\Advanced2D.h"
#include "GameManager.h"
#include "InputController.h"

using namespace Advanced2D;
// version to use

//camera object
Camera *camera1;
Camera *camera2;
Light *light;
Light *light2;
GameManager *gameManager;

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
	//load all audio using this format
	if (!g_engine->audio->Load("gong.ogg", "gong")) {
		g_engine->message("Error loading gong.ogg");
		return false;
	}

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

//  g_engine->SetAmbient(D3DCOLOR_RGBA(255,255,255,0));
	
	// Setup custom classes
	gameManager = new GameManager();
  
    return 1;
}

void game_update() 
{
	gameManager->Update();
	
	// use to slow game update calls if needed
	updateDelay++;
	if (updateDelay > 51)
		updateDelay = 0;
}

void game_keyRelease(int key) 
{
	if (key == DIK_T)
	{
		g_engine->audio->Play("gong");
		ToggleCamera();
	}
	else
		gameManager->PassKeyReleaseInput(key);
}

void game_keyPress(int key) 
{
	if (key != DIK_ESCAPE && key != DIK_T && key != DIK_RETURN)
		gameManager->PassKeyPressInput(key);
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
	delete light2;
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
void game_controllerButtonPressed(int index, int button)
{
	gameManager->PassKeyPressInput(button);
}
void game_controllerButtonReleased(int index, int button)
{
	gameManager->PassKeyReleaseInput(button);
}
void game_controllerButtonDown(int index, int button){}
void game_controllerLeftTrigger(int index, int value){}
void game_controllerRightTrigger(int index, int value){}
void game_controllerThumbLX(int index, float value){}
void game_controllerThumbLY(int index, float value){}
void game_controllerThumbRX(int index, float value) {}
void game_controllerThumbRY(int index, float value) {}