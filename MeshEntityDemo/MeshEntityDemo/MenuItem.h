#ifndef MENUITEM_H
#define MENUITEM_H

#include "..\..\Engine\Advanced2D.h"

class MenuItem
{
public:
	MenuItem(std::string _text, Advanced2D::GAMESTATE _toState);
	virtual ~MenuItem(void);
	std::string getText();
	Advanced2D::GAMESTATE getGoToState();
private:
	std::string text;
	Advanced2D::GAMESTATE goToState;
};
#endif

