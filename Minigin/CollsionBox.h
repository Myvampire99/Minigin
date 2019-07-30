#pragma once
class CollisionBox : public CollisionObject
{
public:
	CollisionBox(dae::Vector2 position,float width,float height,float margin = 0,bool IsPointInMiddle = false);
	~CollisionBox();

	bool CheckPointsIfInside(const std::vector<dae::Vector2> &Points) const override;
private:
	float m_Width;
	float m_Heigth;
	float m_Margin;
};

