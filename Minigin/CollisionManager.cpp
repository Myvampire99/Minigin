#include "MiniginPCH.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	for (auto p : m_Objects)
		delete p;

	m_Objects.clear();
}

void CollisionManager::Update() {

	for (auto object : m_Objects) {
		object->ClearAllCollisions();
	}

	for (auto objectI : m_Objects) {
		for (auto objectJ : m_Objects) {
			if (objectI != objectJ) {
				if (objectI->CheckPointsIfInside(objectJ->GetAllPoints())) {
					objectI->AddCollision(objectJ);
					objectJ->AddCollision(objectI);
				}
			}
		}
	}
}
void CollisionManager::RemoveAll() {
	for (auto object : m_Objects) {
		delete object;
	}
	m_Objects.clear();
}

void CollisionManager::AddCollision(CollisionObject* object) {
	m_Objects.push_back(object);
}

void CollisionManager::Remove(CollisionObject* object) {
	for (int i{}; i < m_Objects.size(); ++i) {
		if (m_Objects[i] == object) {
			delete m_Objects[i];
			m_Objects[i] = nullptr;
			m_Objects.erase(m_Objects.begin() + i);
		}
		
	}
}
