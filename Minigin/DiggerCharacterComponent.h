#pragma once
#include "BaseCharacterComponent.h"

class DiggerCharacterComponent : public BaseCharacterComponent
{
public:
	DiggerCharacterComponent(GridLevel* level);
	~DiggerCharacterComponent();

	void Fire();
	void LocalUpdate(float elapsedTime) override;
	void Draw() override;
private:
	GridLevel* m_Level;
	int m_LastID;
	enum FireStates {
		Throwing,
		Attached,
		Idle
	};
	FireStates m_FireState;
	float m_ThrowingSpeed,m_CurrentElapsedThrow;
	dae::Transform m_CurrentThrowPos;
	float m_DistanceThrow;

	std::shared_ptr<dae::Texture2D> m_Sling;
	int fire;//TODO: change this hardcoded thing
	void localIni() override;
};

