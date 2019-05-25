#include "MiniginPCH.h"
#include "PookaState.h"
//PookaState::~PookaState()
//{
//}


WanderingState::WanderingState() : m_CurrentDir() {
	//TODO: Hardcoded
	//dae::Singleton<InputManager>::GetInstance().AssignButton(ControllerButton::Button_Y, new ChangeToPlayerC);
}

void PookaState::ChangeToPlayer() {
	if (dynamic_cast<WanderingState*>(this))
		Changed = m_PlayerState;
	if (dynamic_cast<PlayerState*>(this))
		Changed = Wandering;
}