#include "MiniginPCH.h"
#include "FPSComponent.h"


FPSComponent::FPSComponent()
{
}

float FPSComponent::GetFps()
{
	return m_FPS;
}

void FPSComponent::Update(const float elapsedTime)
{
	
	m_ElapsedTime += elapsedTime;
}

void FPSComponent::Draw()
{
	it++;
	if (m_ElapsedTime > 1) {
		m_FPS = (float)it;
		m_ElapsedTime = 0;
		it = 0;
	}
}

void FPSComponent::Initialize()
{
}

