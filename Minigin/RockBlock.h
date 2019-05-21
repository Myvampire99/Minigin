#pragma once
#include "LevelObject.h"
class CollisonManager;
class CollisionObject;
class Subject;
class RockBlock :
	public LevelObject
{
public:
	RockBlock(std::string path, GridLevel* m_Level,CollisionObject* collision);
	~RockBlock();

	void Update(float elapsedTime) override;
	void Initialize() override;

	void SetSubject(Subject *subject);
private:
	GridLevel* m_Level;
	float m_FallSpeed;
	bool m_Falling;
	float CurrentZone;

	float m_TimeBeforeFall;
	float m_CurrentFall;

	Subject *m_Subject;
};

