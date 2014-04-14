#include "UI.h"

UI::UI(void)
{
}

void UI::LoadSprites()
{
	// load all sprites, and pass into g_engine->addEntity
	Advanced2D::Sprite *sprite = new Advanced2D::Sprite();
	sprite->loadImage("title_screen.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::MAIN_MENU);
	g_engine->addEntity(sprite);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("main_menu.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::PAUSE);
	g_engine->addEntity(sprite);

	Advanced2D::Sprite *sprite2 = new Advanced2D::Sprite();
	sprite2->loadImage("ring_sprite.png");
	sprite2->setDrawState(Advanced2D::GAMESTATE::GAME_PLAY);
	float x = sprite2->getWidth()/2;
	sprite2->setPosition(g_engine->getScreenWidth()/2 - x, 800);
		
	sprite = new Advanced2D::Sprite();
	sprite->loadImage("power_sprite.png");
	sprite->setName("power_sprite");
	sprite->setDrawState(Advanced2D::GAMESTATE::GAME_PLAY);
	sprite->setPosition(g_engine->getScreenWidth()/2 - x, 800);
	sprite->setWidth(100);
	sprite->setCurrentFrame(0);
	sprite->setColumns(5);
	g_engine->addEntity(sprite);
	// add ring sprite after the power so it is behind it, 
	// but we must grab it before hand to position elements
	g_engine->addEntity(sprite2);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("arrow_sprite.png");
	sprite->setName("arrow_sprite");
	sprite->setDrawState(Advanced2D::GAMESTATE::GAME_PLAY);
	sprite->setPosition(g_engine->getScreenWidth()/2 - x, 780);
	g_engine->addEntity(sprite);
	

}

void UI::UpdateAngle(float _new)
{
	// alter power angle to new rotation
}
void UI::UpdateVisuals (Advanced2D::GAMESTATE _perState)
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
			} else {currentEntity->setVisible(false);}
		}
		iter++;
	}
}

UI::~UI(void)
{
}
