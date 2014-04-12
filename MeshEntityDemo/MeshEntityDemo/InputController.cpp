#include "InputController.h"

InputController::InputController(int _angleUp, int _angleDown, int _shoot) :
	angleCap(0.01),
	shotAngle(0),
	bShoot(false)
{
	angleUpButton = _angleUp;
	angleDownButton = _angleDown;
	shootButton = _shoot;
}

void InputController::ButtonPress(int _key)
{
	if (_key == angleUpButton)
	{
		if (shotAngle < angleCap)
			shotAngle += 0.005f;
	}
	else if (_key == angleDownButton)
	{
		if (shotAngle > -angleCap)
			shotAngle -= 0.005f;
	}
	else if (_key == shootButton)
		bShoot = true;
}

void InputController::ButtonRelease(int _key)
{
	if (_key == shootButton)
		bShoot = false;
}

bool InputController::SetAngleUpBtn(int _new)
{
	// Ensure new button is not one used by gameManager
	if (_new != DIK_ESCAPE && _new != DIK_T && _new != DIK_RETURN)
	{
		angleUpButton = _new; 
		return true;
	}
	return false;
}

bool InputController::SetAngleDownBtn(int _new)
{
	// Ensure new button is not one used by gameManager
	if (_new != DIK_ESCAPE && _new != DIK_T && _new != DIK_RETURN)
	{
		angleDownButton = _new; 
		return true;
	}
	return false;
}

bool InputController::SetShootBtn(int _new)
{
	// Ensure new button is not one used by gameManager
	if (_new != DIK_ESCAPE && _new != DIK_T && _new != DIK_RETURN)
	{
		shootButton = _new; 
		return true;
	}
	return false;
}

InputController::~InputController(void)
{
}
