#include "MiniginPCH.h"
#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{
	for (auto coll : m_Collisions) {
		dae::Singleton<CollisionManager>::GetInstance().Remove(coll);
	}
}

void CollisionComponent::AddCollision(CollisionObject* object) {
	dae::Singleton<CollisionManager>::GetInstance().AddCollision(object);
	m_Collisions.push_back(object);
}

const std::vector<CollisionObject*>& CollisionComponent::GetCollisions() {
	return m_Collisions;
}

void CollisionComponent::Remove(CollisionObject* object) {

	
	for (unsigned int i{}; i < m_Collisions.size(); ++i) {
		if (m_Collisions[i] == object) {
			dae::Singleton<CollisionManager>::GetInstance().Remove(m_Collisions[i]);
			m_Collisions.erase(m_Collisions.begin() + i);
		}
	}

	dae::Singleton<CollisionManager>::GetInstance().Remove(object);
}


void CollisionComponent::Update(const float elapsedTime) { UNREFERENCED_PARAMETER(elapsedTime); 

for (auto coll : m_Collisions)
	coll->SetPosition(m_GameObject->GetTransform()->GetPosition2D());

}	

void CollisionComponent::Draw()  {}
void CollisionComponent::Initialize()  {}