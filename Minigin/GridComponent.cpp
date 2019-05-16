#include "MiniginPCH.h"
#include "GridComponent.h"


GridComponent::GridComponent(GridLevel *level)
	:m_Level{ level }
{}

GridComponent::~GridComponent()
{
}

void GridComponent::Update(const float elapsedTime) {

	UNREFERENCED_PARAMETER(elapsedTime);

	auto pos = m_Level->GetClosestPosOnLine(m_GameObject->GetPos());
	m_GameObject->SetPosition(pos.x, pos.y);
	

}

void GridComponent::Draw() {}
void GridComponent::Initialize() {}
