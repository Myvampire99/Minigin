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
	GridLevel* m_GridLevel;
	InputComponent* m_Inputcomponent;
	DiggerCharacterComponent* m_PlayerCharacter;

	enum Actions
	{
		left, right, up, down,fire
	};
};

