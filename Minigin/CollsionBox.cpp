#include "MiniginPCH.h"
#include "CollsionBox.h"
//named wrong

CollisionBox::CollisionBox(dae::Vector2 position, float width, float height,float margin, bool IsPointInMiddle)
	:CollisionObject()
	, m_Width{ width }
	, m_Heigth{ height }
	, m_Margin{margin}
{

	if (margin > 0)
		std::cout << "test";

	//[0] will always be the start position
	//anticlockwise
	if (!IsPointInMiddle) {
		m_Points.push_back({ position.x + margin, position.y + margin });
		m_Points.push_back({ position.x + width + margin,position.y + margin });
		m_Points.push_back({ position.x + width + margin,position.y + height + margin });
		m_Points.push_back({ position.x + margin,position.y + height + margin });
	}
	else
	{
		m_Points.push_back({ position.x - width / 2.f + m_Margin,position.y - height / 2.f + m_Margin });
		m_Points.push_back({ position.x + width / 2.f + m_Margin,position.y - height / 2.f + m_Margin });
		m_Points.push_back({ position.x + width / 2.f + m_Margin,position.y + height / 2.f + m_Margin });
		m_Points.push_back({ position.x - width / 2.f + m_Margin,position.y + height / 2.f + m_Margin });
	}
}


CollisionBox::~CollisionBox()
{
}

bool CollisionBox::CheckPointsIfInside(const std::vector<dae::Vector2> &Points) const{
	// {0,0} is left top
	for (auto point : Points) {
		if (point.x >= m_Points[0].x && point.x <= m_Points[0].x + m_Width
		&& point.y >= m_Points[0].y && point.y <= m_Points[0].y + m_Heigth)
		{
			return true;
		}
	}
	return false;
}