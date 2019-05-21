#pragma once
#include "BaseCharacterComponent.h"

class CollisionObject;
class CollisionComponent;
class DiggerCharacterComponent : public BaseCharacterComponent
{
public:
	DiggerCharacterComponent(GridLevel* level);//, CollisionComponent* collision);
	~DiggerCharacterComponent();

	void Fire();
	void LocalUpdate(float elapsedTime) override;
	void Draw() override;
	void SetWidth(float width);

	bool IsDigging();
	int GetLives();
	void SetLives(int lives);

private:
	GridLevel* m_Level;
	int m_LastID;
	enum FireStates {
		Throwing,
		Attached,
		Idle
	};

	//CollisionObject* m_Collision;

	FireStates m_FireState;
	float m_ThrowingSpeed,m_CurrentElapsedThrow;
	dae::Transform m_CurrentThrowPos;
	float m_DistanceThrow;

	std::shared_ptr<dae::Texture2D> m_Sling;
	int fire;//TODO: change this hardcoded thing
	void localIni() override;

	bool m_IsDigging;
	float m_WidthSprite;

	CollisionObject* m_PumpColl;
	std::shared_ptr<dae::GameObject> m_AttachedEnemy;
	float m_CurrentElapsedAttached;
	float m_InflationTime;
	bool m_PressedInflationButton;

	int m_Lives;
};

