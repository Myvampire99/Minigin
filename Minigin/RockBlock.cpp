#include "MiniginPCH.h"
#include "RockBlock.h"


RockBlock::RockBlock(std::string path, GridLevel* m_Level, CollisionObject* collision)
	:LevelObject(path)
	, m_Level{ m_Level }
	, m_FallSpeed{50}
	, m_Falling{false}
	,CurrentZone{0}
	, m_TimeBeforeFall{1}
	, m_CurrentFall{0}
{
	dae::Singleton<CollisionManager>::GetInstance().AddCollision(collision);
	m_Collision = collision;
}


RockBlock::~RockBlock()
{
}

void RockBlock::SetSubject(Subject *subject) {
	m_Subject = subject;
}


void RockBlock::Update(float elapsedTime) {

	float Beginzone = 0.5f;
	float Latezone = 1.1f;
	CurrentZone = Latezone;

	if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos(this->GetPos()), GridLevel::Dir::Down)) && !m_Falling)
	{
		m_Level->FreeBlock(this, new EmptyBlock);
		m_Falling = true;
		CurrentZone = Beginzone;
	}

	if (m_Falling)
	{
		if (m_CurrentFall > m_TimeBeforeFall) {

			if ((!dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos({ this->GetPos().x, this->GetPos().y - m_Level->GetBlockSize() }), GridLevel::Dir::Up))))
				CurrentZone = Latezone;
			else
				CurrentZone = Beginzone;

			if ((!dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetClosestIDViaPos({ this->GetPos().x, this->GetPos().y - m_Level->GetBlockSize()*CurrentZone }), GridLevel::Dir::Down)))) {
				m_Falling = false;
				m_Level->LockBlock(this, m_Level->GetClosestIDViaPos(this->GetPos()));
				m_CurrentFall = 0;
			}
			else {
				dae::Vector2 position = this->GetPos();
				position.y += m_FallSpeed * elapsedTime;
				this->SetPos(position);
			}

			
		}
		else {
			m_CurrentFall += elapsedTime;
		}
	}

	m_Collision->SetPosition(this->GetPos());

	if (m_Falling) {
		int count = (int)m_Collision->GetCurrentCollisions().size();
		if (count != 0) {
			for (auto coll : m_Collision->GetCurrentCollisions()) {
				
					for (auto &player : dae::Singleton<ServiceLocator>::GetInstance().GetPlayers()) {
						if (player->GetComponent<CollisionComponent>()->GetCollisions().size() > 0) {
							if (player->GetComponent<CollisionComponent>()->GetCollisions()[0] == coll)
							{
								m_Subject->Notify(player.get(), Event::EVENT_DIED);//TODO: Smart to Raw Pointer, chagne this
							}
						}
					}

				
			}
		}
	}

}



void RockBlock::Initialize() {


}