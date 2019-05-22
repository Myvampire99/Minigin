#include "MiniginPCH.h"
#include "GridComponent.h"


GridComponent::GridComponent(GridLevel *level, bool slide)
	:m_Level{ level }
	, m_Slide{ slide }
	, m_LastPos{  }
{}

GridComponent::~GridComponent()
{
}



void GridComponent::Update(const float elapsedTime) {

	UNREFERENCED_PARAMETER(elapsedTime);

	auto prepos = m_GameObject->GetPos();

	auto offsetPosition{ m_GameObject->GetPos() };
	auto pos = m_Level->GetClosestPosOnLine(offsetPosition);

	auto coll = m_GameObject->GetComponent<CollisionComponent>()->GetCollisions();
	
	for (auto collision : coll) {
		if (collision->GetCurrentCollisions().size() == 0) {
			m_GameObject->SetPosition(pos.x, pos.y);
			
				if (!(prepos == m_GameObject->GetPos())) {
					if (m_Slide) {
						if (m_LastPos == m_GameObject->GetPos()) {
							m_GameObject->SetPosition(pos.x + 1, pos.y + 1);
						}
					}
				}
				else {
					m_prevprevPos = m_prevPos;
					m_prevPos = m_LastPosGO;
					m_LastPosGO = prepos;
				}
			
		}
		else {
				m_GameObject->SetPosition(m_prevprevPos.x, m_prevprevPos.y );
				dae::Vector2 temp = { m_prevprevPos .x - m_LastPosGO.x,m_prevprevPos.y - m_LastPosGO.y };
				m_GameObject->GetTransform()->Translate(temp);
		}
	}
	
	
	m_LastPos = pos;
}

void GridComponent::SetSlide(bool slide) {
	m_Slide = slide;
}

void GridComponent::Draw() {}
void GridComponent::Initialize() {}
