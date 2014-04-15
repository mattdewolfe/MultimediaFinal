#include "InputController.h"

InputController::InputController(int _angleUp, int _angleDown, int _shoot) :
	angleCap(0.01),
	shotAngle(0),
	shotPower(0.01),
	bShoot(false)
{
	angleUpButton = _angleUp;
	angleDownButton = _angleDown;
	shootButton = _shoot;
}

void InputController::ButtonPress(int _key, Advanced2D::GAMESTATE _perState)
{
	if (_perState == Advanced2D::GAME_PLAY)
	{
		if (_key == angleUpButton)
		{
			if (shotAngle < angleCap)
				shotAngle += 0.002f;
		}
		else if (_key == angleDownButton)
		{
			if (shotAngle > -angleCap)
				shotAngle -= 0.002f;
		}
		else if (_key == shootButton)
			bShoot = true;
	}
}

void InputController::ButtonRelease(int _key, Advanced2D::GAMESTATE _perState, Menu *_menu)
{
	if (_perState == Advanced2D::MAIN_MENU)
	{
		if (_key == angleUpButton)
		{
			_menu->selectionUp();
		}
		else if (_key == angleDownButton)
		{
			_menu->selectionDown();
		}
	}
	else if (_perState == Advanced2D::PAUSE)
	{
		if (_key == angleUpButton)
		{
			_menu->selectionUp();
		}
		else if (_key == angleDownButton)
		{
			_menu->selectionDown();
		}
	}
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

void InputController::incrementShotPower()
{
	shotPower += 0.01;
	if (shotPower > 0.06)
		shotPower = 0.01;
}

InputController::~InputController(void)
{
}
