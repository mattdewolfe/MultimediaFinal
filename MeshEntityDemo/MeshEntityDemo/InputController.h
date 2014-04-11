#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
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
};
#endif

