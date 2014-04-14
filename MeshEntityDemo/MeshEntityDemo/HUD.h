#ifndef HUD_H
#define HUD_H

#include "..\..\Engine\Advanced2D.h"

class HUD
{
public:
	HUD(void);
	virtual ~HUD(void);
	void show(float _angle, float _power, int _time);
private:
	//hud font
	Advanced2D::Font *verdana10;
	//hud sprites
	Advanced2D::Sprite* arrow;
	Advanced2D::Sprite* circle;
	Advanced2D::Sprite* powerBars;
};
#endif

