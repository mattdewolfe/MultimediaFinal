#ifndef UI_H
#define UI_H

#include "..\..\Engine\Advanced2D.h"

class UI
{
public:

	UI(void);
	virtual ~UI(void);
	void Update();
	void LoadSprites();
	void DrawVisuals(Advanced2D::GAMESTATE _perState);
};
#endif

