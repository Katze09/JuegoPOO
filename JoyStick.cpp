#include "JoyStick.h"

JoyStick::JoyStick() {}

JoyStick::JoyStick(SDL_Joystick* joy) 
{
	this->joy = joy;
}

JoyStick::~JoyStick()
{
	SDL_JoystickClose(joy);
}

int JoyStick::joyDirection() 
{

    Sint16 x = SDL_JoystickGetAxis(joy, 0);
    Sint16 y = SDL_JoystickGetAxis(joy, 1);

    int direction = 0; // 0: Ninguna dirección

    if (x < -10000) 
        direction = 1; // Izquierda
    else if (x > 10000) 
        direction = 2; // Derecha

    if (y < -10000) 
        direction = 3; // Arriba
    else if (y > 10000) 
        direction = 4; // Abajo

    // Diagonales
    if (x < -10000 && y < -10000) 
        direction = 5; // Arriba-Izquierda
    else if (x > 10000 && y < -10000) 
        direction = 6; // Arriba-Derecha
    else if (x < -10000 && y > 10000) 
        direction = 7; // Abajo-Izquierda
    else if (x > 10000 && y > 10000) 
        direction = 8; // Abajo-Derecha
    return direction;
}
