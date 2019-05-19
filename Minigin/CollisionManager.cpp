#include "MiniginPCH.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
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

void CollisionManager::AddCollision(CollisionObject* object) {
	m_Objects.push_back(object);
}

void CollisionManager::Remove(CollisionObject* object) {
	for (int i{}; i < m_Objects.size(); ++i) {
		if (m_Objects[i] == object)
			m_Objects.erase(m_Objects.begin() + i);
	}
}
