#pragma once
#include "BaseComponent.h"
class AIComponent :
	public BaseComponent
{
public:
	AIComponent(InputComponent* input, BaseCharacterComponent *pooka);
	~AIComponent();

	void Update(float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

	PookaState *GetState();
private:
	bool m_Enabled;
	PookaState *m_State;
	PookaState *m_ChangedState;

	InputComponent *m_Input;
	BaseCharacterComponent *m_Pooka;
	WanderingState *m_Wandering;
	PlayerState *m_PlayerState;
};

