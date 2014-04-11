#include "InputController.h"

InputController::InputController(int _angleUp, int _angleDown, int _shoot) :
	angleUpButton(119), 
	angleDownButton(115), 
	shootButton(32), 
	bShoot(false), 
	bAngleUp(false), 
	bAngleDown(false)
{
	angleUpButton = _angleUp;
	angleDownButton = _angleDown;
	shootButton = _shoot;
}

void InputController::ButtonPress(int _key)
{
	if (_key == angleUpButton)
		bAngleUp = true;
	else if (_key == angleDownButton)
		bAngleDown = true;
	else if (_key == shootButton)
		bShoot = true;
}
void InputController::ButtonRelease(int _key)
{
	if (_key == angleUpButton)
		bAngleUp = false;
	else if (_key == angleDownButton)
		bAngleDown = false;
	else if (_key == shootButton)
		bShoot = false;
}
InputController::~InputController(void)
{
}
