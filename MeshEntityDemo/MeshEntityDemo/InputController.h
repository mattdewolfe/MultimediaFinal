#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "..\..\Engine\Advanced2D.h"

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

	void ButtonPress(int _key);
	void ButtonRelease(int _key);
	bool CheckFire() { return bShoot; }

#pragma region Get/Set
	bool SetAngleUpBtn(int _new);
	int GetAngleUpBtn() { return angleUpButton; }

	bool SetAngleDownBtn(int _new);
	int GetAngleDownBtn() { return angleDownButton; }

	bool SetShootBtn(int _new);
	int GetShootBtn() { return shootButton; }
	
	float GetShotAngle() { return shotAngle; }

	void SetShotPower(int _pow) { shotPower = (1 + _pow) * 0.01; }
	
	float GetShotPower() { return shotPower; }
	
	void SetFireFalse () { bShoot = false; }
#pragma endregion Get/Set
};
#endif

