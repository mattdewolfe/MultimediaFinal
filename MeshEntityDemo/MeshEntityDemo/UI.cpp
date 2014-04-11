#include "UI.h"

UI::UI(void)
{
}

void UI::LoadSprites()
{
	Advanced2D::Sprite *sprite = new Advanced2D::Sprite();
	sprite->loadImage("title_screen.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::MAIN_MENU);
	g_engine->addEntity(sprite);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("main_menu.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::PAUSE);
	g_engine->addEntity(sprite);

	sprite = new Advanced2D::Sprite();
	sprite->loadImage("target_line2.png");
	sprite->setDrawState(Advanced2D::GAMESTATE::GAME_PLAY);
	g_engine->addEntity(sprite);
	// load all sprites, and pass into g_engine->addEntity
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
