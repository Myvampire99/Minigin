#include "MiniginPCH.h"
#include "FygarCharacterComponent.h"


FygarCharacterComponent::FygarCharacterComponent(GridLevel *level)
	:BaseCharacterComponent()
	, m_InflatesBeforeDeath{ 3 }
	, m_CurrentInflation{}
	, m_Level{ level }
	, m_PrevPos{}
	, ScoreIfDead{ 400 }
	, m_IsBreathingFire{false}
	, m_CurrentElapsedTimeFire{0}
	, m_MaxElapsedTimeFire{1.f}
	, fire{ 4 }
{

	m_2DFire = dae::ResourceManager::GetInstance().LoadTexture("Resources/Textures/fire.png");
	m_WHFire.y = m_2DFire->GetHeight();
	m_WHFire.x = m_2DFire->GetWidth();

	m_Fire = new CollisionBox({ 0.f,0.f }, m_WHFire.x, m_WHFire.y);
	m_Fire->SetIsTrigger(true);
	dae::Singleton<CollisionManager>::GetInstance().AddCollision(m_Fire);

}

void FygarCharacterComponent::BreathFire() {
	m_IsBreathingFire = true;
}

FygarCharacterComponent::~FygarCharacterComponent()
{
}

int FygarCharacterComponent::GetScore() {
	int layers = 4;
	for (int i{1}; i < layers+1; ++i) {
		if (m_GameObject->GetPos().y > m_Level->GetPosFromID(0).y + m_Level->GetHeight() / i*m_Level->GetBlockSize()) {
			return int(ScoreIfDead * i);
		}
	}

	return (int)ScoreIfDead;
}

void FygarCharacterComponent::SetSubject(Subject * sub) {
	m_Subject = sub;
}

int FygarCharacterComponent::GetInflateState() {
	return m_CurrentInflation;
}

void FygarCharacterComponent::SetInflationState(int inf) {
	m_CurrentInflation = inf;
	if (m_CurrentInflation > m_InflatesBeforeDeath)
		m_Subject->Notify(m_GameObject, Event::EVENT_DIED);
}

void FygarCharacterComponent::LocalUpdate(const float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);

	if (m_IsBreathingFire) {
		m_CurrentElapsedTimeFire += elapsedTime;
		m_Fire->SetPosition(m_GameObject->GetPos());
		auto m_FirePos = *m_GameObject->GetTransform();
		m_FirePos.Translate({ m_WHFire.x ,0 });
		m_Fire->SetPosition(m_FirePos.GetPosition2D());

		int count = (int)m_Fire->GetCurrentCollisions().size();
		if (count != 0) {
			for (auto coll : m_Fire->GetCurrentCollisions()) {
				if (!coll->IsTrigger()) {
					for (auto &player : dae::Singleton<ServiceLocator>::GetInstance().GetPlayers()) {
						if (player->GetComponent<CollisionComponent>()->GetCollisions().size() > 0) {
							if (player->GetComponent<CollisionComponent>()->GetCollisions().size() > 0) {
								if (player->GetComponent<CollisionComponent>()->GetCollisions()[0] == coll)
								{
									if (dynamic_cast<DiggerCharacterComponent*>(player->GetComponent<DiggerCharacterComponent>()))
										m_Subject->Notify(player.get(), Event::EVENT_DIED);
								}
							}
						}
					}

				}
			}
		}

		if (m_CurrentElapsedTimeFire > m_MaxElapsedTimeFire) {
			m_CurrentElapsedTimeFire = 0;
			m_IsBreathingFire = false;
		}
	}

	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithPos(m_GameObject->GetPos()))) {

		m_PrevPos = m_GameObject->GetPos();
	}
	else
	{
		m_GameObject->SetPosition(m_PrevPos.x, m_PrevPos.y);
	}

	if (m_CurrentInflation > 3)
		m_GameObject->MarkForDelete();

	emptyDir.rem();

	int ID = m_Level->GetClosestIDViaPos(m_GameObject->GetPos());

	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Up)))
		emptyDir.up = true;
	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Down)))
		emptyDir.down = true;
	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Left)))
		emptyDir.left = true;
	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Right)))
		emptyDir.right = true;

	auto collision = m_GameObject->GetComponent<CollisionComponent>()->GetCollisions()[0];
	



	int count = (int)collision->GetCurrentCollisions().size();
	if (count != 0) {
		for (auto coll : collision->GetCurrentCollisions()) {
			if (!coll->IsTrigger()) {
				for (auto &player : dae::Singleton<ServiceLocator>::GetInstance().GetPlayers()) {
					if (player->GetComponent<CollisionComponent>()->GetCollisions().size() > 0) {
						if (player->GetComponent<CollisionComponent>()->GetCollisions()[0] == coll)
						{
							if (dynamic_cast<DiggerCharacterComponent*>(player->GetComponent<DiggerCharacterComponent>()))
								m_Subject->Notify(player.get(), Event::EVENT_DIED);
						}
					}
				}

			}
		}
	}

}


PookaCharacterComponent::EmptyDir FygarCharacterComponent::GetEmptyDir() {
	return emptyDir;
}


void FygarCharacterComponent::Draw() {

	if (m_IsBreathingFire) {
		float scale = m_GameObject->GetTransform()->GetScale();

		int width{}, height{};
		SDL_QueryTexture(m_2DFire->GetSDLTexture(), nullptr, nullptr, &width, &height);

		dae::Renderer::GetInstance().RenderTexture(*m_2DFire, { m_GameObject->GetPos().x , m_GameObject->GetPos().y }, { 0,0 }, { (float)width,(float)height }, { (float)width,(float)height }, m_GameObject->GetTransform()->GetAngle(), { (float)width / 4.f,height / 2.f }, false, false, scale);
	}
}

void FygarCharacterComponent::localIni() {
	dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(4), new FygarFire(), m_Input->GetPlayerID());
}