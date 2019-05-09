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
	m_FPS = 1000 / elapsedTime;
}

void FPSComponent::Draw()
{
}

void FPSComponent::Initialize()
{
}

