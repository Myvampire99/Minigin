#pragma once
class CoopLevel :public dae::Scene
{
public:
	CoopLevel();
	~CoopLevel();


	void SceneUpdate() override;
	void SceneInitialize() override;

private:
	std::shared_ptr<dae::GameObject> m_Player;
	std::shared_ptr<dae::GameObject> m_Player2;
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
		left, right, up, down, fire
	};
};

