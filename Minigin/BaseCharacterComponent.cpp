#include "MiniginPCH.h"
#include "BaseCharacterComponent.h"


BaseCharacterComponent::BaseCharacterComponent()
	:m_Speed{100}
{
	
}


BaseCharacterComponent::~BaseCharacterComponent()
{
}

void BaseCharacterComponent::Update(const float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//if need update use inputocmpnent//TODO: Convert to commands
///	if(m_Input->NeedUpdate())//TODO: Convert to commands
	//{
	//	if(dae::Singleton<InputManager>::GetInstance().IsPressed(m_Input->GetButton(Xleft)))//TODO: Convert to commands
	//		Xforward(elapsedTime, -1);
	//	if (dae::Singleton<InputManager>::GetInstance().IsPressed(m_Input->GetButton(Xright)))//TODO: Convert to commands
	//		Xforward(elapsedTime, 1);
	//	if (dae::Singleton<InputManager>::GetInstance().IsPressed(m_Input->GetButton(Ydown)))//TODO: Convert to commands
	//		Yforward(elapsedTime, -1);
	//	if (dae::Singleton<InputManager>::GetInstance().IsPressed(m_Input->GetButton(Yup)))//TODO: Convert to commands
	//		Yforward(elapsedTime, 1);
	//}
	
}

void BaseCharacterComponent::Xforward(const float elapsedTime,int direction)
{
	float speedX = m_Speed * elapsedTime*direction;
	auto pos2 = m_GameObject->GetPos();
	pos2.x += speedX;
	m_GameObject->SetPosition(pos2.x,pos2.y);
}

void BaseCharacterComponent::Yforward(const float elapsedTime, int direction)
{
	float speedY = m_Speed * elapsedTime*direction;
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
	//
	Command *command = new GoRight(this);
	dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Xleft), command);
	//
}