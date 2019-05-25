#pragma once
#include "BaseCharacterComponent.h"
class FygarCharacterComponent :
	public BaseCharacterComponent
{
public:
	FygarCharacterComponent(GridLevel *level);
	~FygarCharacterComponent();

	int GetInflateState();
	void SetInflationState(int inf);
	void Draw() override;
	void BreathFire();
	void localIni() override;

private:
	int fire;

	CollisionBox *m_Fire;
	bool m_IsBreathingFire;
	float m_CurrentElapsedTimeFire;
	float m_MaxElapsedTimeFire;

	int m_InflatesBeforeDeath;
	int m_CurrentInflation;

	GridLevel *m_Level;
	void LocalUpdate(const float elapsedTime) override;

	dae::Vector2 m_PrevPos;
	dae::Vector2 m_WHFire;

private:
	PookaCharacterComponent::EmptyDir emptyDir;
	float ScoreIfDead;
	Subject *m_Subject;
	std::shared_ptr<dae::Texture2D> m_2DFire;
public:
	PookaCharacterComponent::EmptyDir GetEmptyDir();

	int GetScore();
	void SetSubject(Subject * sub);
};