#pragma once
#include "LevelObject.h"
class BorderBlock :
	public LevelObject
{
public:
	BorderBlock(CollisionBox* coll);
	~BorderBlock();

	void Update(float elapsedTime) override;
	void Initialize()override;

private:
	CollisionBox* m_Coll;
};

