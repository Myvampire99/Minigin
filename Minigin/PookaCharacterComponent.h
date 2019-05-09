#pragma once
#include "BaseCharacterComponent.h"
class PookaCharacterComponent :
	public BaseCharacterComponent
{
public:
	PookaCharacterComponent();
	~PookaCharacterComponent();

	int GetInflateState();
	void SetInflationState(int inf);

private:
	int m_InflatesBeforeDeath;
	int m_CurrentInflation;

};

