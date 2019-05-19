#include "MiniginPCH.h"
#include "CollisionObject.h"


CollisionObject::CollisionObject()
	:m_IsTrigger{false}
{
}

CollisionObject::~CollisionObject()
{
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

void CollisionObject::SetPosition(dae::Vector2 newPosition) {

	dae::Vector2 offset{};
	offset.x = m_Points[0].x - newPosition.x;
	offset.y = m_Points[0].y - newPosition.y;
	offset.x = -offset.x;
	offset.y = -offset.y;

	for (auto &pos : m_Points) {
		pos = pos + offset;
	}

}

dae::Vector2 CollisionObject::GetPosition() {
	return m_Points[0];
}