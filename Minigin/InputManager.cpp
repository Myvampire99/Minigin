#include "MiniginPCH.h"
#include "InputManager.h"

InputManager::InputManager()
	:m_ControllerConected{false}
{
	for (int i{}; i < XUSER_MAX_COUNT; ++i) {
		m_Buttons.push_back({});
		m_Released.push_back({});
		m_NeedToRelease.push_back({});
	}
	


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

	
	m_KeyDown = false;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeyDown = true;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool InputManager::IsKeyDown()
{
	return m_KeyDown;
}

std::pair<bool, int> InputManager::IsPressed(ControllerButton button, int player, bool Keyboard)
{

	if (!Keyboard) {
		if ((m_States[player].Gamepad.wButtons & (WORD)button) == (WORD)button) {
			if(m_NeedToRelease[player][button])
			     m_Released[player][button] = true;
			else
				return { true, player };
		}
		else {
			if (m_Released[player][button] == true) {
				m_Released[player][button] = false;
				return { true, player };
			}
		}
			
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
			    if (IsPressed(button.first, i, false).first) {
				///	std::cout << "Button" << std::endl;
				    button.second->Execute(IsPressed(button.first, i, false).second);
				}
					
		

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

void InputManager::AssignButton(ControllerButton button, Command *pointer,int player, bool release )
{

	m_NeedToRelease[player][button] = release;
	m_Released[player][button] = false;

	if (m_Buttons[player][button])
		delete m_Buttons[player][button];
	
	m_Buttons[player][button] = pointer;
}

void InputManager::ForceButton(ControllerButton button, int player) {
	m_States[player].Gamepad.wButtons |= (WORD)button;
	m_SkipPlayer[player] = true;

}
