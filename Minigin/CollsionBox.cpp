#include "MiniginPCH.h"
#include "CollsionBox.h"
//named wrong

CollisionBox::CollisionBox(dae::Vector2 position, float width, float height,bool IsPointInMiddle)
	:CollisionObject()
	, m_Width{ width }
	, m_Heigth{ height }
{
	//[0] will always be the start position
	//anticlockwise
	if (!IsPointInMiddle) {
		m_Points.push_back(position);
		m_Points.push_back({ position.x + width,position.y });
		m_Points.push_back({ position.x + width,position.y + height });
		m_Points.push_back({ position.x,position.y + height });
	}
	else
	{
		m_Points.push_back({ position.x - width / 2.f,position.y - height / 2.f });
		m_Points.push_back({ position.x + width / 2.f,position.y - height / 2.f });
		m_Points.push_back({ position.x + width / 2.f,position.y + height / 2.f });
		m_Points.push_back({ position.x - width / 2.f,position.y + height / 2.f });
	}
}


CollisionBox::~CollisionBox()
{
}

bool CollisionBox::CheckPointsIfInside(const std::vector<dae::Vector2> &Points) const{
	// {0,0} is left top
	for (auto point : Points) {
		if (point.x > m_Points[0].x && point.x < m_Points[0].x + m_Width
		&& point.y > m_Points[0].y && point.y < m_Points[0].y + m_Heigth)
		{
			return true;
		}
	}
	return false;
}