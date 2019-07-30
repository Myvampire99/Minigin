#include "MiniginPCH.h"
#include "CollisionObject.h"


CollisionObject::CollisionObject()
	:m_IsTrigger{false}
	, m_CollisionComponent{ nullptr }
	, m_PreviousPos{}
	, m_Margin{}
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::SetMargin(dae::Vector2 margin) {
	m_Margin = margin;
}

const std::vector<dae::Vector2> &CollisionObject::GetAllPoints() {
	return m_Points;
}

void CollisionObject::SetCurrentCollisions(const std::vector<CollisionObject*> &collisions) {
	m_CurrentCollisions = collisions;
}

void CollisionObject::AddCollision(CollisionObject* collisions) {
	for (auto col : m_CurrentCollisions) {
		if (col == collisions)
			return;
	}
	m_CurrentCollisions.push_back(collisions);
}

void CollisionObject::ClearAllCollisions() {
	m_CurrentCollisions.clear();
}

const std::vector<CollisionObject*> &CollisionObject::GetCurrentCollisions() const {
	return m_CurrentCollisions;
}

void CollisionObject::SetIsTrigger(bool istrigger) {
	m_IsTrigger = istrigger;
}

bool CollisionObject::IsTrigger() {
	return m_IsTrigger;
}

//Local Position
void CollisionObject::SetPosition(dae::Vector2 newPosition) {

	dae::Vector2 offset{};
	offset.x = m_Points[0].x - newPosition.x;
	offset.y = m_Points[0].y - newPosition.y;
	offset.x = -offset.x;
	offset.y = -offset.y;

	for (auto &pos : m_Points) {
		pos = pos + offset + m_Margin;
	}

}

dae::Vector2 CollisionObject::GetPosition() {
	return m_Points[0];
}

CollisionComponent* CollisionObject::GetComponent() {
	return m_CollisionComponent;
}

void CollisionObject::SetComponent(CollisionComponent* col) {
	m_CollisionComponent = col;
}

void CollisionObject::SetPrevPos(dae::Vector2 pos) {
	m_PreviousPos = pos;
}

dae::Vector2 CollisionObject::GetPrevPos() {
	return m_PreviousPos;
}