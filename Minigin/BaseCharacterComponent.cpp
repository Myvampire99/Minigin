#include "MiniginPCH.h"
#include "BaseCharacterComponent.h"


BaseCharacterComponent::BaseCharacterComponent()
	:m_Speed{100}
	, ForceStop{false}
	, m_DirectionState{}
	, DirectionWithoutIdle{}
{}


BaseCharacterComponent::~BaseCharacterComponent()
{
}

void BaseCharacterComponent::Update(const float elapsedTime)
{
	

	UNREFERENCED_PARAMETER(elapsedTime);
	//Maybe if no InputComponent, do other things
	if(m_Input->NeedUpdate())
	{
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Xleft), new PlayerLeft());
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Xright), new PlayerRight());
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Yup), new PlayerUp());
		dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(Ydown), new PlayerDown());
	}
	LocalUpdate(elapsedTime);

	m_DirectionState = Direction::Idle;

}

void BaseCharacterComponent::LocalUpdate(const float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
}

void BaseCharacterComponent::Xforward(int direction)
{
	if (!ForceStop) {
		float speedX = m_Speed * dae::Singleton<ServiceLocator>::GetInstance().GetElapsedTime()*direction;
		auto pos2 = m_GameObject->GetPos();
		pos2.x += speedX;
		m_GameObject->SetPosition(pos2.x, pos2.y);
	
		if (direction == 1) {
			m_DirectionState = Direction::Right;
			m_GameObject->GetTransform()->SetAngle(0.f);
		}
		else {
			m_DirectionState = Direction::Left;
			m_GameObject->GetTransform()->SetAngle(180.f);
		}

	}
}

void BaseCharacterComponent::Yforward(int direction)
{
	if (!ForceStop) {
		float speedY = m_Speed * dae::Singleton<ServiceLocator>::GetInstance().GetElapsedTime()*direction;
		auto pos2 = m_GameObject->GetPos();
		pos2.y += speedY;
		m_GameObject->SetPosition(pos2.x, pos2.y);
	
		if (direction == 1) {
			m_DirectionState = Direction::Up;
			m_GameObject->GetTransform()->SetAngle(90.f);
		}
		else {
			m_DirectionState = Direction::Down;
			m_GameObject->GetTransform()->SetAngle(-90.f);
		}
	}
}

void BaseCharacterComponent::AssignButton(int XLEFT, int XRIGHT, int YUP, int YDOWN)
{
	Xleft = XLEFT;
	Xright = XRIGHT;
	Yup = YUP;
	Ydown = YDOWN;

}


void BaseCharacterComponent::Initialize()
{
	m_Input = m_GameObject->GetComponent<InputComponent>();
	localIni();
}

void BaseCharacterComponent::Draw() {

}

void BaseCharacterComponent::localIni() {

}

std::pair<bool, bool> BaseCharacterComponent::GetFlipVertnFlipHor() {

	if(m_DirectionState != Idle)
		DirectionWithoutIdle = m_DirectionState;

	if (DirectionWithoutIdle == Direction::Left || DirectionWithoutIdle == Direction::Down)
		if (DirectionWithoutIdle == Direction::Left)
			return std::make_pair<bool, bool>(false, true);
		else if(DirectionWithoutIdle == Direction::Down)
			return std::make_pair<bool, bool>(true, false);

		return std::make_pair<bool, bool>(false, false);
}

BaseCharacterComponent::Direction BaseCharacterComponent::GetDirection() {
	return m_DirectionState;
}