#pragma once
class DebugScene : public dae::Scene
{
public:
	DebugScene(std::string name = "DebugScene");
	~DebugScene();

	void SceneUpdate() override;
	void SceneInitialize() override;
	void SwitchSceneIni() override;
	void SwitchSceneDec() override;

private:

	GridManager* m_GridManager;
	InputComponent* m_Inputcomponent;
	BaseCharacterComponent* m_PlayerCharacter;
	std::shared_ptr<dae::GameObject> m_Player;
	std::vector<std::shared_ptr<dae::GameObject>> m_SnoBee;
	std::vector<std::shared_ptr<dae::GameObject>> m_SnoBeeEgg;

	std::shared_ptr<dae::GameObject> m_Score;
	std::shared_ptr<dae::GameObject> m_Health;

	int m_IntHealth;
	int m_IntSnoBeeRemaining;

	void LocalReset() override;//TODO: what is this ?
	void CreateAnIceBlock(int ID, float margin);
	void CreateAnIceBlockEgg(int ID, float margin);
	void CreateSnoBee(dae::Vector2 pos, int p);
};

