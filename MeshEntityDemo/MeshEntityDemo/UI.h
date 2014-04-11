#ifndef UI_H
#define UI_H

#include "..\..\Engine\Advanced2D.h"

class UI
{
public:
	UI(void);
	virtual ~UI(void);
	void UpdateAngle(float _angle);
	void LoadSprites();
	void UpdateVisuals(Advanced2D::GAMESTATE _perState);
};
#endif

