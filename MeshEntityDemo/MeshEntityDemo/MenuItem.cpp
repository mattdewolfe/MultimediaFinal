#include "MenuItem.h"

MenuItem::MenuItem(std::string _text, Advanced2D::GAMESTATE _toState)
{
	text = _text;
	goToState = _toState;
}

MenuItem::~MenuItem(void)
{
}

std::string MenuItem::getText()
{
	return text;
}

Advanced2D::GAMESTATE MenuItem::getGoToState()
{
	return goToState;
}