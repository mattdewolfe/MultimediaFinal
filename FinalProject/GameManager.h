#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "..\Engine\Advanced2D.h"
#include "ObjectFactory.h"
#include "HUD.h"

class GameManager {

public:
	ObjectFactory objectFactory;
	
	GameManager();
	virtual ~GameManager();
	void DrawVisuals();
	void CheckFlags();
	void Update();

private:

};

#endif


