#include "MiniginPCH.h"
#include "ServiceLocator.h"


ServiceLocator::ServiceLocator()
	:ElapsedTime{0}
{
}


ServiceLocator::~ServiceLocator()
{
}

std::shared_ptr<dae::GameObject>& ServiceLocator::GetPlayersObject(int playerID) {
	return m_Players[playerID];
}

const std::vector<std::shared_ptr<dae::GameObject>>& ServiceLocator::GetPlayers() {
	return m_Players;
}

void ServiceLocator::SetPlayerObject(const std::shared_ptr<dae::GameObject>& object) {
	m_Players.push_back(object);
}

void ServiceLocator::RemovePlayerObject(const dae::GameObject* object) {

	for (int i{}; i < m_Players.size(); ++i) {
		if (m_Players[i].get() == object) {
			m_Players.erase(m_Players.begin() + i);
		}

	}

}

void ServiceLocator::RemoveAllPlayerObjects() {

	m_Players.clear();

}

float ServiceLocator::GetElapsedTime() {
	return ElapsedTime;
}

void ServiceLocator::SetElapsedTime(float et) {
	ElapsedTime = et;
}

void ServiceLocator::SetGOScore(std::shared_ptr<dae::GameObject> score) {
	m_Score = score;
}

void ServiceLocator::SetGOHealth(std::shared_ptr<dae::GameObject> health) {
	m_Health = health;
}

std::shared_ptr<dae::GameObject> ServiceLocator::GetScoreGO() {
	return m_Score;
}

std::shared_ptr<dae::GameObject> ServiceLocator::GetHealthGO() {
	return m_Health;
}

int ServiceLocator::GetCurrentScore() {
	return m_CurrentScore;
}

void ServiceLocator::AddCurrentScore(int score) {
	m_CurrentScore += score;
}

void ServiceLocator::SetCurrentScore(int score) {
	m_CurrentScore = score;
}
