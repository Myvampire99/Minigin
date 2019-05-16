#pragma once
#include "BaseComponent.h"
class GridComponent : public BaseComponent
{
public:
	GridComponent(GridLevel *level);
	~GridComponent();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;
private:
	GridLevel* m_Level;

};

