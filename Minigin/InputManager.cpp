#include "MiniginPCH.h"
#include "InputManager.h"

InputManager::InputManager()
	:m_ControllerConected{false}
{
	for (int i{};i< XUSER_MAX_COUNT;++i)
		m_Buttons.push_back({});
}

InputManager::~InputManager() {
	for (auto players : m_Buttons){
		for (auto p : players) {
			delete p.second;
		}
	}

}

bool InputManager::ProcessInput()
{
	KeyState = SDL_GetKeyboardState(NULL);

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

std::pair<bool, int> InputManager::IsPressed(ControllerButton button, int player, bool Keyboard) const
{
	if (!Keyboard) {
		if ((m_States[player].Gamepad.wButtons & (WORD)button) == (WORD)button)
			return { true, player };
	}
	else {
		if (GetKeyboardState((PBYTE)button))
			return { true, 0 };
	}
	return { false,0 };

}

void InputManager::HandleInput()
{
	int i{0};
	for (auto& players : m_Buttons)
	{
		for (auto& button : players)
		{
				if (IsPressed(button.first, i, false).first)
					button.second->Execute(IsPressed(button.first, i, false).second);
		

				if (IsPressed(button.first, i, true).first)
					button.second->Execute(IsPressed(button.first, i, false).second);
		}
		i++;
	}

	for (DWORD j = 0; j < XUSER_MAX_COUNT; ++j)
	{
		m_States[j].Gamepad.wButtons = 0;
		m_SkipPlayer[j] = false;
	}

}

void InputManager::AssignButton(ControllerButton button, Command *pointer,int player)
{
	m_Buttons[player][button] = pointer;
}

void InputManager::ForceButton(ControllerButton button, int player) {
	m_States[player].Gamepad.wButtons |= (WORD)button;
	m_SkipPlayer[player] = true;
}
