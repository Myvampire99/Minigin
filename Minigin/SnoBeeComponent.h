#pragma once
#include "BaseCharacterComponent.h"
class SnoBeeComponent : public BaseCharacterComponent
{
public:
	SnoBeeComponent(GridManager* grid);
	~SnoBeeComponent();

	void localIni() override;
	void LocalUpdate(const float elapsedTime) override;

	void BreakBlock();
private:
	GridManager* m_GridManager;
};

