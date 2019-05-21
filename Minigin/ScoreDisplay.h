#pragma once
#include "Observer.h"
class ScoreDisplay :
	public Observer
{
public:
	ScoreDisplay();
	~ScoreDisplay();
	void onNotify(dae::GameObject* entity, Event event) override;
private:
};

