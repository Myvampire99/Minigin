#pragma once
class ServiceLocator
{
public:
	ServiceLocator();
	~ServiceLocator();

	std::shared_ptr<dae::GameObject>& GetPlayersObject(int playerID);
	void SetPlayerObject(const std::shared_ptr<dae::GameObject>& object);
	const std::vector<std::shared_ptr<dae::GameObject>>& GetPlayers();

	float GetElapsedTime();
	void SetElapsedTime(float et);

	void SetGOScore(std::shared_ptr<dae::GameObject> score);
	void SetGOHealth(std::shared_ptr<dae::GameObject> health);

	std::shared_ptr<dae::GameObject> GetScoreGO();
	std::shared_ptr<dae::GameObject> GetHealthGO();

	int GetCurrentScore();
	void AddCurrentScore(int score);
	void SetCurrentScore(int score);

	void RemovePlayerObject(const dae::GameObject* object);
	void RemoveAllPlayerObjects();

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Players;
	float ElapsedTime;

	std::shared_ptr<dae::GameObject> m_Score;
	std::shared_ptr<dae::GameObject> m_Health;

	int m_CurrentScore;
};

