#pragma once
#include "BaseComponent.h"
class SnoBeeEgg : public BaseComponent
{
public:
	SnoBeeEgg();
	~SnoBeeEgg();

	void Update(float elapsedTime) override;
	void Draw() override;
	void Initialize() override;
};

