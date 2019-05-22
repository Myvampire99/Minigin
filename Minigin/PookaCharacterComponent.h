#pragma once
#include "BaseCharacterComponent.h"
class PookaCharacterComponent :
	public BaseCharacterComponent
{
public:
	PookaCharacterComponent(GridLevel *level);
	~PookaCharacterComponent();

	int GetInflateState();
	void SetInflationState(int inf);

private:
	int m_InflatesBeforeDeath;
	int m_CurrentInflation;

	GridLevel *m_Level;
	void LocalUpdate(const float elapsedTime) override;

	dae::Vector2 m_PrevPos;
public:
	struct EmptyDir {
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		void rem() {
			up = down = left = right = false;
		}
	};
private:
	EmptyDir emptyDir;
	float ScoreIfDead;
	Subject *m_Subject;
public:
	EmptyDir GetEmptyDir();

	int GetScore();
	void SetSubject(Subject * sub);
};

