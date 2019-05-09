#pragma once
#include "BaseComponent.h"
class FPSComponent : public BaseComponent
{
public:
	FPSComponent();
	~FPSComponent() = default;
	//rule of 5

	float GetFps();
protected:
	virtual void Update(const float elapsedTime) override;
	virtual void Draw() override;
	virtual void Initialize() override;

private:
	float m_FPS;
};

