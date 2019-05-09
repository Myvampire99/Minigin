#include "MiniginPCH.h"
#include "PookaCharacterComponent.h"


PookaCharacterComponent::PookaCharacterComponent()
	:BaseCharacterComponent()
	, m_InflatesBeforeDeath{3}
	, m_CurrentInflation{}
{
}


PookaCharacterComponent::~PookaCharacterComponent()
{
}


int PookaCharacterComponent::GetInflateState() {
	return m_CurrentInflation;
}

void PookaCharacterComponent::SetInflationState(int inf) {
	m_CurrentInflation = inf;
}