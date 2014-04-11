#ifndef UI_H
#define UI_H

#include "..\..\Engine\Advanced2D.h"
#include "GamePlayStates.h"

class UI : public virtual GamePlayStates
{
public:
	Advanced2D::Sprite* visuals[4];
	UI(void);
	virtual ~UI(void);
	void Update();
	void LoadSprites();
	void HideVisuals(GAMESTATE _perState);
};
#endif

