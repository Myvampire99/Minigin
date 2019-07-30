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

	object->SetComponent(this);//First Set Component
	dae::Singleton<CollisionManager>::GetInstance().AddCollision(object);
	m_Collisions.push_back(object);
}

const std::vector<CollisionObject*>& CollisionComponent::GetCollisions() {
	return m_Collisions;
}

void CollisionComponent::Remove(CollisionObject* object) {
	//TODO: Remove Component
	
	for (unsigned int i{}; i < m_Collisions.size(); ++i) {
		if (m_Collisions[i] == object) {
			dae::Singleton<CollisionManager>::GetInstance().Remove(m_Collisions[i]);
			m_Collisions.erase(m_Collisions.begin() + i);
		}
	}

	dae::Singleton<CollisionManager>::GetInstance().Remove(object);
}


void CollisionComponent::Update(const float elapsedTime) { UNREFERENCED_PARAMETER(elapsedTime); 

for (auto coll : m_Collisions) {
	coll->SetPosition(m_GameObject->GetTransform()->GetPosition2D());

	//DEBUG only boxes
	auto points = coll->GetAllPoints();
	if(coll->IsTrigger())
		DD::GetInstance().DrawQuad(points.at(0), {  points.at(1).x - points.at(0).x , points.at(3).y - points.at(0).y });
	else
		DD::GetInstance().DrawQuad(points.at(0), { points.at(1).x - points.at(0).x , points.at(3).y - points.at(0).y },1);
	//

}
	



}	

void CollisionComponent::Draw()  {}
void CollisionComponent::Initialize()  {}