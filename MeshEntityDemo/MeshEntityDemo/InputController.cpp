#include "InputController.h"

InputController::InputController(int _angleUp, int _angleDown, int _shoot) :
	angleUpButton(119), 
	angleDownButton(115), 
	shootButton(32)
{
	angleUpButton = _angleUp;
	angleDownButton = _angleDown;
	shootButton = _shoot;
}


InputController::~InputController(void)
{
}
