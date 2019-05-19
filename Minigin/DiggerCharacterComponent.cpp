#include "MiniginPCH.h"
#include "DiggerCharacterComponent.h"

DiggerCharacterComponent::DiggerCharacterComponent(GridLevel* level)//, CollisionComponent* collision)
	: BaseCharacterComponent()
	, m_Level(level)
	, m_LastID(0)
	, m_FireState{ Idle }
	, m_ThrowingSpeed{ 100 }
	, m_CurrentThrowPos{}
	, m_DistanceThrow{ 150 }
	, fire{ 4 }
	, m_IsDigging{ false }
	, m_WidthSprite{}
{
	//m_Collision = collision->GetCollisions()[0];
	m_Sling = dae::ResourceManager::GetInstance().LoadTexture("Resources/Textures/sling.png");
}

DiggerCharacterComponent::~DiggerCharacterComponent()
{
}

void DiggerCharacterComponent::SetWidth(float width) {
	m_WidthSprite = width;
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
		//break;
	}
	//
	m_IsDigging = false;

	

	if (m_WidthSprite != 0) {
		switch (m_DirectionState) {
		case Left:
		
			if (!dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos({ m_GameObject->GetPos().x ,m_GameObject->GetPos().y }),GridLevel::Dir::Left)))
				m_IsDigging = true;
			break;
		case Right:
			if (!dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos({ m_GameObject->GetPos().x + m_WidthSprite,m_GameObject->GetPos().y }), GridLevel::Dir::Right)))
			
				m_IsDigging = true;
			break;
		case Down:
			if (!dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos({ m_GameObject->GetPos().x ,m_GameObject->GetPos().y }), GridLevel::Dir::Up)))//TODO: wtf up and down are switched
				m_IsDigging = true;
			break;
		case Up:
			if (!dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos({ m_GameObject->GetPos().x ,m_GameObject->GetPos().y}), GridLevel::Dir::Down)))//TODO: wtf up and down are switched
				m_IsDigging = true;
			break;
		default:;
		}
	}
	


}

bool DiggerCharacterComponent::IsDigging() {
	return m_IsDigging;
}


//TODO: Draw in the base
void DiggerCharacterComponent::Draw() {

	float scale = m_GameObject->GetTransform()->GetScale();

	int width{}, height{};
	SDL_QueryTexture(m_Sling->GetSDLTexture(), nullptr, nullptr, &width, &height);
	//TODO: somewhere else
	//width *= (int)scale;
	//height *= (int)scale;

	m_DistanceThrow = (float)width;
	//
	//dae::Vector2 destWH{ m_CurrentThrowPos.GetPosition2D().x - m_GameObject->GetPos().x , (float)height};
	dae::Vector2 destWH{ m_CurrentThrowPos.GetPosition2D().DistanceTo({m_GameObject->GetPos().x ,m_GameObject->GetPos().y}), (float)height };
	dae::Vector2 src{ width - destWH.x,0.f };
	

	//dae::Renderer::GetInstance().RenderTexture(*m_Sling, m_GameObject->GetPos(), src, destWH, destWH);
	
	//TODO: not needed to draw if not action
	
	
	




	
	dae::Renderer::GetInstance().RenderTexture(*m_Sling, { m_GameObject->GetPos().x , m_GameObject->GetPos().y }, src, destWH, destWH, m_GameObject->GetTransform()->GetAngle(), { (float)width/4.f,height / 2.f }, false, false, scale);
	//m_Sprites[m_CurrentState]->Draw(m_GameObject->GetPos(), scale, m_FlipSpriteVert, m_FlipSpriteHor, m_GameObject->GetTransform()->GetAngle(), center);
	
	
	

	



	



	//	dae::Renderer::GetInstance().RenderTexture(*m_Sling, m_GameObject->GetPos(), src, destWH, destWH, m_GameObject->GetTransform()->GetAngle(), m_GameObject->GetPos());
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