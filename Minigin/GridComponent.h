#pragma once
#include "BaseComponent.h"
class GridComponent : public BaseComponent
{
public:
	GridComponent(GridManager *level, bool slide = false);
	~GridComponent();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

	void SetSlide(bool slide);
private:
	GridManager* m_Level;
	bool m_Slide;

	dae::Vector2 m_LastPos;
	dae::Vector2 m_LastPosGO;
	dae::Vector2 m_prevPos;
	dae::Vector2 m_prevprevPos;
};

