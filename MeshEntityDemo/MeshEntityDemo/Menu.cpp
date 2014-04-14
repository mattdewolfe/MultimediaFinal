#include "Menu.h"

Menu::Menu(Advanced2D::Sprite *_background)
{
	verdana10 = new Advanced2D::Font();
	if (!verdana10->loadImage("verdana10.tga")) {
		g_engine->message("Error loading verdana10.tga");
	}
	verdana10->setColumns(16);
	verdana10->setCharSize(20, 16);

	if (!verdana10->loadWidthData("verdana10.dat")) {
		g_engine->message("Error loading verdana10.dat");
	}
	verdana10->setScale(2.0);
	background = _background;
	currentSelection = 0;
}

Menu::~Menu(void)
{
}

void Menu::show()
{
	background->draw();
	for (int i = 0; i < menuItems.size(); i++)
	{
		MenuItem *menuItem = menuItems[i];
		if (currentSelection == i)
		{
			verdana10->Print(g_engine->getScreenWidth() / 2 - 40, 240 + 80 * i, menuItem->getText(), 0xFF000000);
		}
		else
		{
			verdana10->Print(g_engine->getScreenWidth() / 2 - 40, 240 + 80 * i, menuItem->getText(), 0xFF991111);
		}
	}
}

void Menu::addItem(std::string _item, Advanced2D::GAMESTATE _toState)
{
	menuItems.push_back(new MenuItem(_item, _toState));
}

void Menu::selectionDown()
{
	currentSelection++;
	if (currentSelection > menuItems.size() - 1)
		currentSelection = 0;
}

void Menu::selectionUp()
{
	currentSelection--;
	if (currentSelection < 0)
		currentSelection = menuItems.size() - 1;
}

MenuItem *Menu::getMenuItem(int _pos)
{
	return menuItems[_pos];
}

int Menu::getCurrentSelection()
{
	return currentSelection;
}