#include "MiniginPCH.h"
#include "InputManager.h"

InputManager::InputManager()
	:m_ControllerConected{false}
{
}

bool InputManager::ProcessInput()
{

	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{ 
		if (!m_SkipPlayer[i]) {
			m_ControllerConected = true;

			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));
			m_States[i] = state;

			DWORD dwResult;
			dwResult = XInputGetState((DWORD)i, &m_States[i]);
			if (dwResult != ERROR_SUCCESS)
				m_ControllerConected = false;
		}
		m_SkipPlayer[i] = false;
	}

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

std::pair<bool, int> InputManager::IsPressed(ControllerButton button) const
{
	for (int i{}; i < XUSER_MAX_COUNT; ++i) {
		if ((m_States[i].Gamepad.wButtons & (WORD)button) == (WORD)button)
			return { true, i };
	}

	if (GetKeyboardState((PBYTE)button))
		return { true, 0 };

	return { false,0 };
}

void InputManager::HandleInput()
{
	for (auto& button : m_Buttons)
	{
		if (IsPressed(button.first).first)
			button.second->Execute(IsPressed(button.first).second);
			
	}
}

void InputManager::AssignButton(ControllerButton button, Command *pointer)
{
	m_Buttons[button] = pointer;
}

void InputManager::ForceButton(ControllerButton button, int player) {
	m_States[player].Gamepad.wButtons = (WORD)button;
	m_SkipPlayer[player] = true;
}
