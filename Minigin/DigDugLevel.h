#pragma once
class DigDugLevel :public dae::Scene
{
public:

	DigDugLevel();
	~DigDugLevel();

	void SceneUpdate() override;
	void SceneInitialize() override;
private:
	std::shared_ptr<dae::GameObject> m_Player;
	std::shared_ptr<dae::GameObject> levelGameObject;
	std::shared_ptr<dae::GameObject> Pooka;
	std::shared_ptr<dae::GameObject> Fygar;
	GridLevel* m_GridLevel;
	InputComponent* m_Inputcomponent;
	DiggerCharacterComponent* m_PlayerCharacter;
	Subject *m_Subject;
	ScoreDisplay *m_ScoreDisplay = nullptr;
	void LocalReset() override;
	enum Actions
	{
		left, right, up, down,fire
	};
};

