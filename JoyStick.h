#pragma once

#include <SDL.h>
#include <iostream>

class JoyStick
{
public:
	JoyStick();
	JoyStick(SDL_Joystick* joy, int indexJoy);
	virtual ~JoyStick();
	int joyDirection();
	bool buttonAShot() { return SDL_JoystickGetButton(joy, 0); }
	bool buttonBSpecial() { return SDL_JoystickGetButton(joy, 1); }
	bool buttonXItemShield() { return SDL_JoystickGetButton(joy, 2); }
	void reconectJoy();
private:
	SDL_Joystick* joy;
	int indexJoy;
};

