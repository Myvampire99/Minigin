#pragma once
#include "LevelObject.h"
class RockBlock :
	public LevelObject
{
public:
	RockBlock(std::string path, GridLevel* m_Level);
	~RockBlock();

	void Update(float elapsedTime) override;
	void Initialize() override;
private:
	GridLevel* m_Level;
};

