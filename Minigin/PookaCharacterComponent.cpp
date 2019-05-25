#include "MiniginPCH.h"
#include "PookaCharacterComponent.h"


PookaCharacterComponent::PookaCharacterComponent(GridLevel *level)
	:BaseCharacterComponent()
	, m_InflatesBeforeDeath{3}
	, m_CurrentInflation{}
	, m_Level{ level }
	, m_PrevPos{}
	, ScoreIfDead{200}
{
}


PookaCharacterComponent::~PookaCharacterComponent()
{
}

int PookaCharacterComponent::GetScore() {
	if (m_GameObject->GetPos().y < m_Level->GetPosFromID(0).y + m_Level->GetHeight() / 2.f*m_Level->GetBlockSize()) {
		return int(ScoreIfDead * 2.f);
	}
	return (int)ScoreIfDead;
}

void PookaCharacterComponent::SetSubject(Subject * sub) {
	m_Subject = sub;
}

int PookaCharacterComponent::GetInflateState() {
	return m_CurrentInflation;
}

void PookaCharacterComponent::SetInflationState(int inf) {
	m_CurrentInflation = inf;
	if(m_CurrentInflation > m_InflatesBeforeDeath)
		m_Subject->Notify(m_GameObject, Event::EVENT_DIED);
}

void PookaCharacterComponent::LocalUpdate(const float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);

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

	int ID = m_Level->GetClosestIDViaPos({ m_GameObject->GetPos().x+10, m_GameObject->GetPos().y });

	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Up)))
		emptyDir.up = true;
	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Down)))
		emptyDir.down = true;
	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Left)))
		emptyDir.left = true;
	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(ID, GridLevel::Dir::Right)))
		emptyDir.right = true;

	auto collision = m_GameObject->GetComponent<CollisionComponent>()->GetCollisions()[0];
	//for (auto cc : collision->GetCurrentCollisions()) {
	//	if (cc == collision) {

	//	}
	//}




	int count = (int)collision->GetCurrentCollisions().size();
	if (count != 0) {
		for (auto coll : collision->GetCurrentCollisions()) {
			if (!coll->IsTrigger()) {
				for (auto &player : dae::Singleton<ServiceLocator>::GetInstance().GetPlayers()) {
					if (player->GetComponent<CollisionComponent>()->GetCollisions().size() > 0) {
						if (player->GetComponent<CollisionComponent>()->GetCollisions()[0] == coll)
						{
							if (dynamic_cast<DiggerCharacterComponent*>(player->GetComponent<DiggerCharacterComponent>()))
							{
								m_Subject->Notify(player.get(), Event::EVENT_DIED);//TODO: Smart to Raw Pointer, chagne this
							}
						}
					}
				}

			}
		}
	}

}


PookaCharacterComponent::EmptyDir PookaCharacterComponent::GetEmptyDir() {
	return emptyDir;
}