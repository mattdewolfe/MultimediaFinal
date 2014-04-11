#include "UI.h"

UI::UI(void)
{
}

void UI::LoadSprites()
{
	// load all sprites, and pass into g_engine->addEntity
}

void UI::HideVisuals(GAMESTATE _perState)
{
	switch(_perState)
	{
	case MAIN_MENU:
		break;
	case GAME_PLAY:
		break;
	case PAUSE:
		break;
	case SCORING:
		break;
	case GAME_OVER:
		break;
	default:
		break;
	}
}

UI::~UI(void)
{
}
