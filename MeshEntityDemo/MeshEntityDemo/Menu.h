#ifndef MENU_H
#define MENU_H

#include "..\..\Engine\Advanced2D.h"
#include "MenuItem.h"
#include <vector>

class Menu
{
public:
	Menu(Advanced2D::Sprite *_background);
	virtual ~Menu(void);
	void show();
	void addItem(std::string, Advanced2D::GAMESTATE _toState);
	void selectionDown();
	void selectionUp();
	MenuItem *getMenuItem(int _pos);
	int getCurrentSelection();
private:
	std::vector<MenuItem*> menuItems;
	int currentSelection;
	Advanced2D::Font *verdana10;
	Advanced2D::Sprite *background;
};
#endif

