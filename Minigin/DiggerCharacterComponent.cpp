#include "MiniginPCH.h"
#include "DiggerCharacterComponent.h"


DiggerCharacterComponent::DiggerCharacterComponent(GridLevel* level)
	:BaseCharacterComponent()
	,m_Level(level)
	, m_LastID(0)
	, m_FireState{Idle}
	, m_ThrowingSpeed{10}
	,m_CurrentThrowPos{}
	, m_DistanceThrow{150}
{}


DiggerCharacterComponent::~DiggerCharacterComponent()
{
}

void DiggerCharacterComponent::LocalUpdate(float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
	int currentID = m_Level->GetClosestIDViaPos(m_GameObject->GetPos());
	//But is the check really enccacry?
	if (currentID + 1 == m_LastID || currentID - 1 == m_LastID || currentID + m_Level->GetWidth() == m_LastID || currentID - m_Level->GetWidth() == m_LastID)//TODO:doesnt check if block next to it is out the level
	{
		if(m_Level->GetObjectWithID(currentID))
			m_Level->ChangeBlock(new EmptyBlock(), currentID);
	}
		
	
	
	m_LastID = currentID;
}

void DiggerCharacterComponent::Fire() {
	float elaspedTime = dae::Singleton<ServiceLocator>::GetInstance().GetElapsedTime();

	switch (m_FireState)
	{
	case FireStates::Idle:

		m_CurrentElapsedThrow = 0;
		m_CurrentThrowPos = m_GameObject->GetPos();


		break;
	case FireStates::Throwing:
	
		m_CurrentElapsedThrow += elaspedTime;
		m_CurrentThrowPos.x += elaspedTime * m_ThrowingSpeed;

		auto object = m_Level->GetObjectWithPos(m_CurrentThrowPos);
		if(typeid(object) != typeid(EmptyBlock))
			m_FireState = FireStates::Idle;

		if (m_GameObject->GetPos().DistanceTo(m_CurrentThrowPos) > m_DistanceThrow) {
			m_FireState = FireStates::Idle;
		}


		break;
	case FireStates::Attached:
		break;
	}

}