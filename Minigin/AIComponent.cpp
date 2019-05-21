#include "MiniginPCH.h"
#include "AIComponent.h"


AIComponent::AIComponent(InputComponent* input, PookaCharacterComponent *pooka)
	:m_Input{ input }
	, m_Pooka{ pooka }
{
	m_State = new WanderingState;//&PookaState::wandering;
}


AIComponent::~AIComponent()
{
}

void AIComponent::Update(float elapsedTime) {
	m_State->update(m_Input, m_Pooka);
	UNREFERENCED_PARAMETER(elapsedTime);
}

void AIComponent::Draw() {

}

void AIComponent::Initialize() {

}