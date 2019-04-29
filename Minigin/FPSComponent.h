#pragma once
#include "BaseComponent.h"
class FPSComponent : public BaseComponent
{
public:
	FPSComponent();
	~FPSComponent() = default;

	float GetFps();
protected:
	virtual void Update(const float elapsedTime) override;
	virtual void Draw() override;
	virtual void Initialize() override;

private:
	float m_FPS;
	float m_ElapsedTime;
	int it;
};

