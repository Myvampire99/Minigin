#pragma once
class ServiceLocator
{
public:
	ServiceLocator();
	~ServiceLocator();

	std::shared_ptr<dae::GameObject>& GetPlayersObject(int playerID);
	void SetPlayerObject(const std::shared_ptr<dae::GameObject>& object);

	float GetElapsedTime();
	void SetElapsedTime(float et);
private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Players;
	float ElapsedTime;
};

