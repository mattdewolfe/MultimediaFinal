#include "..\Engine\Advanced2D.h"
#include "GameManager.h"

using namespace Advanced2D;

//camera object
Camera *camera;
Camera *camera2;
Light *light;
Light *light2;
GameManager gameManager;
#define MAX 10

bool game_preload() 
{
    g_engine->setAppTitle("Hole in Ball");
    g_engine->setFullscreen(false);
    g_engine->setScreenWidth(1600);
    g_engine->setScreenHeight(900);
    g_engine->setColorDepth(32);    
    return 1;
}

bool game_init(HWND) 
{
    //set the camera and perspective
    camera = new Camera();
    camera->setPosition(0.0f, 2.0f, 100.0f);
    camera->setTarget(0.0f, 0.0f, 0.0f);
    camera->Update();
	camera2 = new Camera();
    camera2->setPosition(0.0f, 2.0f, -100.0f);
    camera2->setTarget(0.0f, 0.0f, 0.0f);
    camera2->Update();

    //create a directional light
    D3DXVECTOR3 pos(0.0f,0.0f,0.0f);
    D3DXVECTOR3 dir(1.0f,0.0f,0.0f);
    light = new Light(0, D3DLIGHT_DIRECTIONAL, pos, dir, 500);
    light->setColor(D3DXCOLOR(0,0,0,0));

	//create a directional light
    D3DXVECTOR3 pos2(15.0f,35.0f,10.0f);
    D3DXVECTOR3 dir2(15.0f,1.0f,10.0f);
    light2 = new Light(0, D3DLIGHT_SPOT, pos2, dir2, 500);
    light2->setColor(D3DXCOLOR(0,0,0,0));

    g_engine->SetAmbient(D3DCOLOR_RGBA(1,1,0,0));

    //load meshes
    Mesh *mesh;
	 mesh = new Mesh();
        mesh->Load("airplane 2.x");
        mesh->SetScale(3.0f,3.0f,3.0f);
        float x = 1;
        float y = 1;
        float z = -4;
        mesh->SetPosition(x,y,z);

        //add mesh to entity manager
        g_engine->addEntity(mesh);

    return 1;
}

void game_update() 
{
    //nothing to do!
}

void game_render3d()
{
    g_engine->ClearScene(D3DCOLOR_RGBA(90,90,90,0));
    g_engine->SetIdentity();
}

void game_keyRelease(int key) 
{ 
    if (key == DIK_ESCAPE) g_engine->Close();
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
    delete camera;
	delete camera2;
    delete light;
}

void game_render2d() { }
void game_keyPress(int key) 
{
	if (key == 27)
		g_engine->Close();
}
void game_mouseButton(int button) { }
void game_mouseMotion(int x,int y) { }
void game_mouseMove(int x,int y) { }
void game_mouseWheel(int wheel) { }
void game_controllerButtonPressed(int index, int button){}
void game_controllerButtonReleased(int index, int button){}
void game_controllerButtonDown(int index, int button){}
void game_controllerLeftTrigger(int index, int value){}
void game_controllerRightTrigger(int index, int value){}
void game_controllerThumbLX(int index, float value){}
void game_controllerThumbLY(int index, float value){}
void game_controllerThumbRX(int index, float value) { }
void game_controllerThumbRY(int index, float value) { }