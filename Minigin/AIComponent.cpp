#include "MiniginPCH.h"
#include "AIComponent.h"


AIComponent::AIComponent(InputComponent* input, BaseCharacterComponent *pooka)
	:m_Input{ input }
	, m_Pooka{ pooka }
{
	m_Wandering = new WanderingState;
	m_PlayerState = new PlayerState;

	m_Wandering->m_PlayerState = m_PlayerState;
	m_PlayerState->Wandering = m_Wandering;

	m_State = m_Wandering;
}

PookaState* AIComponent::GetState() {
	return m_State;
}


AIComponent::~AIComponent()
{
	delete m_State;
	m_State = nullptr;

	/*delete m_Wandering;
	m_Wandering = nullptr;

	delete m_PlayerState;
	m_PlayerState = nullptr;

	delete m_ChangedState;
	m_ChangedState = nullptr;*/
}




void AIComponent::Update(float elapsedTime) {
	
	m_ChangedState = m_State->update(m_Input, m_Pooka);

	if (m_ChangedState != m_State && m_ChangedState != nullptr)
		m_State = m_ChangedState;

	UNREFERENCED_PARAMETER(elapsedTime);
}

void AIComponent::Draw() {

}

void AIComponent::Initialize() {

}