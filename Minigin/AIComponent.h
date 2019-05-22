#pragma once
#include "BaseComponent.h"
class AIComponent :
	public BaseComponent
{
public:
	AIComponent(InputComponent* input, PookaCharacterComponent *pooka);
	~AIComponent();

	void Update(float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

private:
	bool m_Enabled;
	PookaState *m_State;

	InputComponent *m_Input;
	PookaCharacterComponent *m_Pooka;
};

