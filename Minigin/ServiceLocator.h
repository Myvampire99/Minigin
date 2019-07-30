#pragma once
class ServiceLocator
{
public:
	ServiceLocator();
	~ServiceLocator();

	std::shared_ptr<dae::GameObject>& GetPlayersObject(int playerID);
	void SetPlayerObject(std::shared_ptr<dae::GameObject> object);
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

	void SetHealth(int hp);
	int GetHealth();

	void ChangePlayerObject(int ID, std::shared_ptr<dae::GameObject> object);
	void RemovePlayerObject(std::shared_ptr<dae::GameObject> object);
	void RemoveAllPlayerObjects();

	int GetSnoBeeRemaining();
	void SetSnoBeeRemaining(int s);

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Players;
	float ElapsedTime;

	std::shared_ptr<dae::GameObject> m_Score;
	std::shared_ptr<dae::GameObject> m_Health;

	int m_CurrentScore;
	int m_CurrentHealth;

	int m_SnoBeeRemaining;
};

