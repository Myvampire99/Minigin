#include "MiniginPCH.h"
#include "InputComponent.h"


InputComponent::InputComponent(int playerid)
	: m_NeedUpdate{false}
	, playerID{playerid}
{
}


InputComponent::~InputComponent()
{
}

int InputComponent::GetPlayerID() {
	return playerID;
}

void InputComponent::AssignButton(int ID, ControllerButton button)
{
	m_Input[ID] = button;
	m_NeedUpdate = true;
}

ControllerButton InputComponent::GetButton(int ID)
{
	return m_Input[ID];
}

bool InputComponent::NeedUpdate()
{
	return m_NeedUpdate;
}

void InputComponent::Update(const float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	if(m_NeedUpdate)
	{
		if(m_ResetUpdate)
		{
			m_NeedUpdate = false;
			m_ResetUpdate = false;
			return;
		}
		m_ResetUpdate = true;
	}else
	{
		m_ResetUpdate = false;
	}

}

void InputComponent::Draw(){}
void InputComponent::Initialize(){}