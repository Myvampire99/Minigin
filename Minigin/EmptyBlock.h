#pragma once
#include "LevelObject.h"
class EmptyBlock :
	public LevelObject
{
public:
	EmptyBlock();
	~EmptyBlock();

	void Update(float elapsedTime) override;
	void Initialize() override;

};

