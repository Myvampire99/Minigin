#pragma once
#include "LevelObject.h"
class CollisonManager;
class CollisionObject;
class RockBlock :
	public LevelObject
{
public:
	RockBlock(std::string path, GridLevel* m_Level,CollisionObject* collision);
	~RockBlock();

	void Update(float elapsedTime) override;
	void Initialize() override;
private:
	GridLevel* m_Level;
	float m_FallSpeed;
	bool m_Falling;
	float CurrentZone;

	float m_TimeBeforeFall;
	float m_CurrentFall;

};

