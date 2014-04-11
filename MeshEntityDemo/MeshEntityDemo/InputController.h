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
	bool bAngleUp, bAngleDown, bShoot;

// Functions
public:
	InputController(int _angleUp, int _angleDown, int _shoot);
	virtual ~InputController(void);

	void SetAngleUpBtn(int _new) { angleUpButton = _new; }
	int GetAngleUpBtn() { return angleUpButton; }

	void SetAngleDownBtn(int _new) { angleDownButton = _new; }
	int GetAngleDownBtn() { return angleDownButton; }

	void SetShootBtn(int _new) { shootButton = _new; }
	int GetShootBtn() { return shootButton; }
	
	void ButtonPress(int _key);
	void ButtonRelease(int _key);
	
	bool CheckAngleUp() { return bAngleUp; }
	bool CheckAngleDown() { return bAngleDown; }
	bool CheckFire() { return bShoot; }
};
#endif

