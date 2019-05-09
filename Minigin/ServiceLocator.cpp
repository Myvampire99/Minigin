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

void ServiceLocator::SetPlayerObject(const std::shared_ptr<dae::GameObject>& object) {
	m_Players.push_back(object);
}

float ServiceLocator::GetElapsedTime() {
	return ElapsedTime;
}

void ServiceLocator::SetElapsedTime(float et) {
	ElapsedTime = et;
}