#include "MiniginPCH.h"
#include "GridComponent.h"


GridComponent::GridComponent(GridManager *level, bool slide)
	:m_Level{ level }
	, m_Slide{ slide }
	, m_LastPos{  }
{}

GridComponent::~GridComponent()
{
}



void GridComponent::Update(const float elapsedTime) {

	UNREFERENCED_PARAMETER(elapsedTime);


	auto column = m_Level->GetAllColumnsX();
	auto row = m_Level->GetAllRowsY();
	float shortestX = 99999.f;
	float shortestY = 99999.f;
	float gridLineX = 0.f;
	float gridLineY = 0.f;
	bool IsOnLine = false;
	dae::Vector2 pos = m_GameObject->GetPos();

	for (int i{}; i < (int)column.size(); ++i) {
		if (column[i] == pos.x) {
			IsOnLine = true;
			break;
		}
		else {
			float distance = std::abs(column[i] - pos.x);
			if (distance < shortestX) {
				shortestX = distance;
				gridLineX = column[i];
			}
				
		}
	}
	
	if (!IsOnLine) {
		for (int i{}; i < (int)row.size(); ++i) {
			if (row[i] == pos.y) {
				IsOnLine = true;
				break;
			}
			else {
				float distance = std::abs(row[i] - pos.y);
				if (distance < shortestY) {
					shortestY = distance;
					gridLineY = row[i];
				}
					
			}
		}
	}

	if (!IsOnLine) {
		if (shortestY < 10.f && shortestX < 10.f) {
			m_GameObject->SetPosition(gridLineX, gridLineY);
		}
		else {
			if (shortestY < shortestX) {
				m_GameObject->SetPosition(pos.x, gridLineY);
			}
			else {
				m_GameObject->SetPosition(gridLineX, pos.y);
			}
		}
	}




	/*auto prepos = m_GameObject->GetPos();

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
			for (auto collis : collision->GetCurrentCollisions()) {
				if (collis->IsTrigger() == false && !(m_LastPosGO == m_prevprevPos)) {
					m_GameObject->SetPosition(m_prevprevPos.x, m_prevprevPos.y);
					dae::Vector2 temp = { m_prevprevPos.x - m_LastPosGO.x,m_prevprevPos.y - m_LastPosGO.y };
					m_GameObject->GetTransform()->Translate(temp);
					break;
				}
			}
		}
	}
	
	
	m_LastPos = pos;*/
}

void GridComponent::SetSlide(bool slide) {
	m_Slide = slide;
}

void GridComponent::Draw() {}
void GridComponent::Initialize() {}
