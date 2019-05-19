#include "MiniginPCH.h"
#include "CollisionComponent.h"


CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::AddCollision(CollisionObject* object) {
	dae::Singleton<CollisionManager>::GetInstance().AddCollision(object);
	m_Collisions.push_back(object);
}

const std::vector<CollisionObject*>& CollisionComponent::GetCollisions() {
	return m_Collisions;
}

void CollisionComponent::Remove(CollisionObject* object) {

	dae::Singleton<CollisionManager>::GetInstance().Remove(object);

	for (int i{}; i < m_Collisions.size(); ++i) {
		if (m_Collisions[i] == object)
			m_Collisions.erase(m_Collisions.begin() + i);
	}
}


void CollisionComponent::Update(const float elapsedTime) { UNREFERENCED_PARAMETER(elapsedTime); 

for (auto coll : m_Collisions)
	coll->SetPosition(m_GameObject->GetTransform()->GetPosition2D());

}	//TODO: Angle from m_GameObject

void CollisionComponent::Draw()  {}
void CollisionComponent::Initialize()  {}