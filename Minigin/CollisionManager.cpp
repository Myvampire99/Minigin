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

	for (auto object : m_Objects) {
		if (!object->IsTrigger()) {
			for (auto currentCol : object->GetCurrentCollisions()) {
				if (!currentCol->IsTrigger()) {
					currentCol->GetComponent()->m_GameObject->SetPosition(currentCol->GetPrevPos());
					object->GetComponent()->m_GameObject->SetPosition(object->GetPrevPos());
				}
			}
		}
	}

	for (auto object : m_Objects) {
		if (!object->IsTrigger()) {
			object->SetPrevPos(object->GetComponent()->m_GameObject->GetPos());
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
	object->SetPrevPos(object->GetComponent()->m_GameObject->GetPos());
	//dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene()->;
	m_Objects.push_back(object);
}

void CollisionManager::onNotify( Event event) {

	switch (event)
	{
	case Event::EVENT_SWITCH_SCENE_DEACTIVATE:
		SwitchScenes(false);//TODO: bool or frame after this one
		break;
	case Event::EVENT_SWITCH_SCENE_ACTIVATE:
		SwitchScenes(true);//TODO: bool or frame after this one
		break;
	}

}

void CollisionManager::SwitchScenes(bool activate) {

	if (activate)
	{
		

		if (m_OtherObjects.size() != 0) {
			for (auto obj : m_OtherObjects) {
				int ID = dae::Singleton<dae::SceneManager>::GetInstance().GetActiveSceneID();
				if (obj.first == ID)
					m_Objects = obj.second;
			}
		}
		
	}
	else {


		if (m_OtherObjects.size() != 0) {
			for (auto obj : m_OtherObjects) {
				int ID = dae::Singleton<dae::SceneManager>::GetInstance().GetActiveSceneID();
				if (obj.first == ID)
					obj.second = m_Objects;
				else
					m_OtherObjects.push_back(std::pair<int, std::vector<CollisionObject*>>(ID, m_Objects));
			}
		}
		else {
			int ID = dae::Singleton<dae::SceneManager>::GetInstance().GetActiveSceneID();
			m_OtherObjects.push_back(std::pair<int, std::vector<CollisionObject*>>(ID, m_Objects));
		}
		m_Objects.clear();
	}
}

void CollisionManager::Remove(CollisionObject* object) {
	for (unsigned int i{}; i < m_Objects.size(); ++i) {
		if (m_Objects[i] == object) {
			delete m_Objects[i];
			m_Objects[i] = nullptr;
			m_Objects.erase(m_Objects.begin() + i);
		}
		
	}
}
