#pragma once
class DigDugLevel :public dae::Scene
{
public:
	DigDugLevel();
	~DigDugLevel();

	void SceneUpdate() override;
	void SceneInitialize() override;
};

