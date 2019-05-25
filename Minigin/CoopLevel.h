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
	GridLevel* m_GridLevel;
	InputComponent* m_Inputcomponent;
	DiggerCharacterComponent* m_PlayerCharacter;
	Subject *m_Subject;
	ScoreDisplay *m_ScoreDisplay = nullptr;
	void SetCopyIni();
	enum Actions
	{
		left, right, up, down, fire
	};
};

