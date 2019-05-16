#pragma once
//#include <XInput.h>
//#include <unordered_map>
/*
#include "Command.h"*/

enum class ControllerButton
{
	Button_A = XINPUT_GAMEPAD_A,
	Button_B = XINPUT_GAMEPAD_B,
	Button_X = XINPUT_GAMEPAD_X,
	Button_Y = XINPUT_GAMEPAD_Y,
	Dpad_Down = XINPUT_GAMEPAD_DPAD_DOWN,
	Dpad_Up = XINPUT_GAMEPAD_DPAD_UP,
	Dpad_Right = XINPUT_GAMEPAD_DPAD_RIGHT,
	Dpad_Left = XINPUT_GAMEPAD_DPAD_LEFT,
	Keyboard_A = VK_ESCAPE

};

class Command;
class InputManager
{
public:
	bool ProcessInput();
	bool IsPressed(ControllerButton button) const;

	InputManager();

	//template<class T>
	void AssignButton(ControllerButton button, Command *pointer);
	void HandleInput();

private:
	std::unordered_map<ControllerButton, Command*> m_Buttons;
	XINPUT_STATE m_States;
	bool m_ControllerConected;
};


//template<class T>