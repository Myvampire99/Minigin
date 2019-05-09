#include "MiniginPCH.h"
#include "BaseCharacterComponent.h"


BaseCharacterComponent::BaseCharacterComponent()
	:m_Speed{100}
{}


BaseCharacterComponent::~BaseCharacterComponent()
{
}

void BaseCharacterComponent::Update(const float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//if need update use inputocmpnent//TODO: Convert to commands
	if(m_Input->NeedUpdate())//TODO: Convert to commands
	{
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Xleft), new PlayerLeft());
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Xright), new PlayerRight());
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Yup), new PlayerUp());
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Ydown), new PlayerDown());
	}
	LocalUpdate(elapsedTime);
}

void BaseCharacterComponent::LocalUpdate(const float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
}

void BaseCharacterComponent::Xforward(int direction)
{
	float speedX = m_Speed * dae::Singleton<ServiceLocator>::GetInstance().GetElapsedTime()*direction;
	auto pos2 = m_GameObject->GetPos();
	pos2.x += speedX;
	m_GameObject->SetPosition(pos2.x,pos2.y);
}

void BaseCharacterComponent::Yforward(int direction)
{
	float speedY = m_Speed * dae::Singleton<ServiceLocator>::GetInstance().GetElapsedTime()*direction;
	auto pos2 = m_GameObject->GetPos();
	pos2.y += speedY;
	m_GameObject->SetPosition(pos2.x, pos2.y);
}

void BaseCharacterComponent::AssignButton(int XLEFT, int XRIGHT, int YUP, int YDOWN)
{
	Xleft = XLEFT;
	Xright = XRIGHT;
	Yup = YUP;
	Ydown = YDOWN;
}

void BaseCharacterComponent::Draw()
{
	
}
void BaseCharacterComponent::Initialize()
{
	
	m_Input = m_GameObject->GetComponent<InputComponent>();
}