#include "MiniginPCH.h"
#include "VelocityComponent.h"


VelocityComponent::VelocityComponent()
	:m_Velocity{}
{
}

VelocityComponent::VelocityComponent(dae::Vector2 vel)
	: m_Velocity{ vel }
{}

VelocityComponent::~VelocityComponent()
{
}

void VelocityComponent::SetVelocity() {

}

void VelocityComponent::Update(float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);

	m_CollisionComponent = m_GameObject->GetComponent<CollisionComponent>();
	if (m_CollisionComponent) {
		for (auto col : m_CollisionComponent->GetCollisions()) {
			for (auto cur : col->GetCurrentCollisions()) {
				if(!cur->IsTrigger())
					m_Velocity = {};
			}
		}
	}

	if (!(m_Velocity == dae::Vector2{0.f,0.f}))
		m_GameObject->GetTransform()->Translate(m_Velocity);

	//if (m_DeleteSelf && m_Velocity.x == 0.f &&  m_Velocity.y == 0.f) {}
}

void VelocityComponent::Draw() {

}

void VelocityComponent::Initialize() {
	m_CollisionComponent = m_GameObject->GetComponent<CollisionComponent>();
}

dae::Vector2 VelocityComponent::GetVelocity() {
	return m_Velocity;
}