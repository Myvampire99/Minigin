#include "MiniginPCH.h"
#include "PookaState.h"


WanderingState::WanderingState() : m_CurrentDir() {}

void PookaState::ChangeToPlayer() {
	if (dynamic_cast<WanderingState*>(this))
		Changed = m_PlayerState;
	if (dynamic_cast<PlayerState*>(this))
		Changed = Wandering;
}