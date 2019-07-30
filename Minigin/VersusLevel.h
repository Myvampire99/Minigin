#pragma once
class VersusLevel : public dae::Scene
{
public:
	VersusLevel(std::string name);
	~VersusLevel();

	void SceneUpdate() override;
	void SceneInitialize() override;
	void SwitchSceneIni() override;
	void SwitchSceneDec() override;

private:
	GridManager* m_GridManager;
	std::shared_ptr<dae::GameObject> m_Player;
	std::vector<std::shared_ptr<dae::GameObject>> m_SnoBee;
	std::vector<std::shared_ptr<dae::GameObject>> m_SnoBeeEgg;

	std::shared_ptr<dae::GameObject> m_Score;
	std::shared_ptr<dae::GameObject> m_Health;

	int m_IntHealth;
	int m_IntSnoBeeRemaining;

	void LocalReset() override;
	void CreateAnIceBlock(int ID);
	void CreateAnIceBlockEgg(int ID);
	void CreateSnoBee(dae::Vector2 pos, int p);
	void CreatePlayer();
	void CreateWall(int start, int max, int inc);

	const int number = 12;
	const int margin = 32;

	Subject* m_Subject;
};

