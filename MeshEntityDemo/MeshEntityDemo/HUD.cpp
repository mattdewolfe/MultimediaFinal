#include "HUD.h"

HUD::HUD(void)
{
	//init font
	verdana10 = new Advanced2D::Font();
	if (!verdana10->loadImage("verdana10.tga")) {
		g_engine->message("Error loading verdana10.tga");
	}
	verdana10->setColumns(16);
	verdana10->setCharSize(20, 16);

	if (!verdana10->loadWidthData("verdana10.dat")) {
		g_engine->message("Error loading verdana10.dat");
	}
	verdana10->setScale(3.0);

	//init all hud sprites
	arrow = new Advanced2D::Sprite();
	arrow->loadImage("sprite3.png");
	arrow->setPosition((g_engine->getScreenWidth() / 2) - (arrow->getWidth() / 2), g_engine->getScreenHeight() - arrow->getHeight());

	circle = new Advanced2D::Sprite();
	circle->loadImage("sprite2.png");
	circle->setPosition((g_engine->getScreenWidth() / 2) - (circle->getWidth() / 2), g_engine->getScreenHeight() - circle->getHeight());

	powerBars = new Advanced2D::Sprite();
	powerBars->loadImage("sprite1.png");
	powerBars->setPosition((g_engine->getScreenWidth() / 2) - (powerBars->getWidth() / 2)/5, g_engine->getScreenHeight() - powerBars->getHeight()-51);
	powerBars->setWidth(127);
	powerBars->setColumns(5);
	powerBars->setCurrentFrame(0);
}

HUD::~HUD(void)
{
}

void HUD::show(float _angle, float _power, int _time)
{
	powerBars->setCurrentFrame((_power*100)-1);
	powerBars->draw();

	circle->draw();

	arrow->setRotation(_angle*30);
	arrow->draw();

	verdana10->Print(10, 50, "Time remaining: " + std::to_string(_time), 0xFF000000);
}