#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "..\..\Engine\Advanced2D.h"
#include "Menu.h"

class InputController
{
// Variables
private:
	// Stores desired angle for shot
	float shotAngle;
	// Stores caps for possible angle - maybe remove and allow shooting 360
	float angleCap;
	// Store power value
	float shotPower;
	// Store button ints for a given controller
	int angleUpButton, angleDownButton, shootButton;
	bool bShoot;

// Functions
public:
	InputController(int _angleUp = DIK_W, int _angleDown = DIK_S, int _shoot = DIK_SPACE);
	virtual ~InputController(void);

	void ButtonPress(int _key, Advanced2D::GAMESTATE _perState);
	void ButtonRelease(int _key, Advanced2D::GAMESTATE _perState, Menu *_menu);
	bool CheckFire() { return bShoot; }
	void incrementShotPower();

#pragma region Get/Set
	bool SetAngleUpBtn(int _new);
	int GetAngleUpBtn() { return angleUpButton; }

	bool SetAngleDownBtn(int _new);
	int GetAngleDownBtn() { return angleDownButton; }

	bool SetShootBtn(int _new);
	int GetShootBtn() { return shootButton; }
	
	float GetShotAngle() { return shotAngle; }
	float GetShotPower() { return shotPower; }
	void SetFireFalse () { bShoot = false; }
#pragma endregion Get/Set
};
#endif

