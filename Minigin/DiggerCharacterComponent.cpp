#include "MiniginPCH.h"
#include "DiggerCharacterComponent.h"

DiggerCharacterComponent::DiggerCharacterComponent(GridLevel* level)
	:BaseCharacterComponent()
	,m_Level(level)
	, m_LastID(0)
	, m_FireState{Idle}
	, m_ThrowingSpeed{300}
	,m_CurrentThrowPos{}
	, m_DistanceThrow{150}
	, fire{4}
{
	m_Sling = dae::ResourceManager::GetInstance().LoadTexture("Resources/Textures/sling.png");
	
}


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


	//fire
	switch (m_FireState)
	{
	case FireStates::Idle:

		m_CurrentElapsedThrow = 0;
		m_CurrentThrowPos = *m_GameObject->GetTransform();
		ForceStop = false;

		break;
	case FireStates::Throwing:
		ForceStop = true;
		m_CurrentElapsedThrow += elapsedTime;

		//m_CurrentThrowPos.x += elapsedTime * m_ThrowingSpeed;
		//m_CurrentThrowPos.SetPosition({ m_CurrentThrowPos.GetPosition().x + elapsedTime * m_ThrowingSpeed , m_CurrentThrowPos.GetPosition().y });
		m_CurrentThrowPos.Translate({ elapsedTime * m_ThrowingSpeed ,0});

		auto debug = m_GameObject->GetPos().DistanceTo(m_CurrentThrowPos.GetPosition2D());
		UNREFERENCED_PARAMETER(debug);
		auto object = m_Level->GetObjectWithPos(m_CurrentThrowPos.GetPosition2D());
		//if (typeid(object) != typeid(EmptyBlock))
		if(!dynamic_cast<EmptyBlock*>(object))
			m_FireState = FireStates::Idle;

		if (m_GameObject->GetPos().DistanceTo(m_CurrentThrowPos.GetPosition2D()) > m_DistanceThrow) {
			m_FireState = FireStates::Idle;
		}


		break;
		//case FireStates::Attached:
		//	break;
	}
	//




}

void DiggerCharacterComponent::Draw() {

	int width{}, height{};
	SDL_QueryTexture(m_Sling->GetSDLTexture(), nullptr, nullptr, &width, &height);
	//TODO: somewhere else
	m_DistanceThrow = (float)width;
	//
	//dae::Vector2 destWH{ m_CurrentThrowPos.GetPosition2D().x - m_GameObject->GetPos().x , (float)height};
	dae::Vector2 destWH{ m_CurrentThrowPos.GetPosition2D().DistanceTo(m_GameObject->GetPos()), (float)height };
	dae::Vector2 src{ width - destWH.x,0.f};


	//dae::Renderer::GetInstance().RenderTexture(*m_Sling, m_GameObject->GetPos(), src, destWH, destWH);
	dae::Renderer::GetInstance().RenderTexture(*m_Sling, m_GameObject->GetPos(), src, destWH, destWH, m_GameObject->GetTransform()->GetAngle(), m_GameObject->GetPos());
	//dae::Renderer::GetInstance().RenderTexture(*m_Sling, m_GameObject->GetPos(), src, destWH, destWH, m_GameObject->GetTransform()->GetAngle(),{0,0});	

	//TODO: {0,0} or _GameObject->GetPos()
}

void DiggerCharacterComponent::Fire() {
	
	if(!ForceStop)//TODO: Maybe other var
		m_FireState = FireStates::Throwing;

}

void DiggerCharacterComponent::localIni() {
	dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(fire), new PlayerFire());//TODO: harcoded for debug purp
}