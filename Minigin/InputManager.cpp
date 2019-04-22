#include "MiniginPCH.h"
#include "InputManager.h"

InputManager::InputManager()
	:m_ControllerConected{false}
{
}

bool InputManager::ProcessInput()
{

	//	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	//{ //For multiple controllers
	// todo: read the input

	m_ControllerConected = true;
	ZeroMemory(&m_States, sizeof(XINPUT_STATE));
	DWORD dwResult;
	dwResult = XInputGetState(0, &m_States);
	if (dwResult != ERROR_SUCCESS)
		m_ControllerConected = false;


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool InputManager::IsPressed(ControllerButton button) const
{
	if ((m_States.Gamepad.wButtons & (WORD)button) == (WORD)button)
		return true;

	if(GetKeyboardState((PBYTE)button))
		return true;

	return false;
}

void InputManager::HandleInput()
{
	for (auto& button : m_Buttons)
	{
		if (IsPressed(button.first))
			button.second->Execute();
			
	}
}


void InputManager::AssignButton(ControllerButton button, Command *pointer)
{
	m_Buttons[button] = pointer;
}
