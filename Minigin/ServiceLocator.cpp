#include "MiniginPCH.h"
#include "ServiceLocator.h"


ServiceLocator::ServiceLocator()
	:ElapsedTime{0}
	, m_SnoBeeRemaining{5}
{
}


ServiceLocator::~ServiceLocator()
{
	m_Players.clear();
}

std::shared_ptr<dae::GameObject>& ServiceLocator::GetPlayersObject(int playerID) {
	return m_Players[playerID];
}

const std::vector<std::shared_ptr<dae::GameObject>>& ServiceLocator::GetPlayers() {
	return m_Players;
}

void ServiceLocator::SetPlayerObject(std::shared_ptr<dae::GameObject> object) {
	m_Players.push_back(object);
}

void ServiceLocator::ChangePlayerObject(int ID, std::shared_ptr<dae::GameObject> object) {
	m_Players[ID] = object;
}

void ServiceLocator::RemovePlayerObject(std::shared_ptr<dae::GameObject> object) {

	for (unsigned int i{}; i < m_Players.size(); ++i) {
		if (m_Players[i] == object) {
			m_Players.erase(m_Players.begin() + i);
		}

	}

}

int ServiceLocator::GetSnoBeeRemaining() {
	return m_SnoBeeRemaining;
}
void ServiceLocator::SetSnoBeeRemaining(int s) {
	m_SnoBeeRemaining = s;
}

void ServiceLocator::SetHealth(int hp) {
	m_CurrentHealth = hp;
}

int ServiceLocator::GetHealth() {
	return m_CurrentHealth;
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
