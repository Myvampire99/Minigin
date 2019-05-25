#pragma once
#include "InputManager.h"
class WanderingState;
class FollowState;
class PlayerState;

class PookaState
{
public:
	//virtual ~PookaState();
	virtual PookaState* update(InputComponent* input, BaseCharacterComponent *pooka) {
		UNREFERENCED_PARAMETER(input); UNREFERENCED_PARAMETER(pooka);
		return nullptr;
	};

	//static WanderingState *wandering;
	PookaState *Wandering;
//	FollowState follow;
	PookaState *m_PlayerState;
	int player = 1;
	PookaState *Changed;

	void ChangeToPlayer();
};

class WanderingState : public PookaState
{
public:
	WanderingState();
	~WanderingState() {}

	PookaState* update(InputComponent* input, BaseCharacterComponent *pooka) override
	{
		PookaCharacterComponent::EmptyDir dir;

		if(dynamic_cast<PookaCharacterComponent*>(pooka))
			dir = dynamic_cast<PookaCharacterComponent*>(pooka)->GetEmptyDir();
		if (dynamic_cast<FygarCharacterComponent*>(pooka)) {
			dir = dynamic_cast<FygarCharacterComponent*>(pooka)->GetEmptyDir();

			int r = std::rand() % 100;
			if (r == 0) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(4), player);//TODO: harcoded
			}
		}
		
		
			

		if (Changed != nullptr) {
			Changed->Changed = nullptr;
			return Changed;
			//Changed = nullptr;
		}
			
		bool m_Skip = false;
		auto currentPos = pooka->GetGameObject()->GetPos();
		if (m_LastPos == currentPos) {
			m_Skip = true;
		}

		m_LastPos = currentPos;

		if (!m_Skip) {
			//TODO: Ugly Code
			if (dir.left && m_CurrentDir.left) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xleft), player);
				m_CurrentDir.rem();
				m_CurrentDir.left = dir.left;
				return nullptr;
			}

			if (dir.up && m_CurrentDir.up) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Yup), player);
				m_CurrentDir.rem();
				m_CurrentDir.up = dir.up;
				return nullptr;
			}

			if (dir.right && m_CurrentDir.right) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xright), player);
				m_CurrentDir.rem();
				m_CurrentDir.right = dir.right;
				return nullptr;
			}

			if (dir.down && m_CurrentDir.down) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Ydown), player);
				m_CurrentDir.rem();
				m_CurrentDir.down = dir.down;
				return nullptr;
			}
		}
		//TODO: Still ugly but loop with m_CurrentDir = true	or something
		int fallback = 100;
		int randomint;
		for (int i{}; i < fallback; ++i){

			randomint = std::rand() % 4;

			if (dir.up && randomint == 0) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Yup), player);
				m_CurrentDir.rem();
				m_CurrentDir.up = dir.up;
				return nullptr;
			}

			if (dir.left&& randomint ==1) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xleft), player);
				m_CurrentDir.rem();
				m_CurrentDir.left = dir.left;
				return nullptr;
			}

			if (dir.down&& randomint == 2) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Ydown), player);
				m_CurrentDir.rem();
				m_CurrentDir.down = dir.down;
				return nullptr;
			}

			if (dir.right&& randomint == 3) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xright), player);
				m_CurrentDir.rem();
				m_CurrentDir.right = dir.right;
				return nullptr;
			}
		}


	
		return nullptr;
	}


	

private:
	PookaCharacterComponent::EmptyDir m_CurrentDir;
	dae::Vector2 m_LastPos{};
};

class FollowState : public PookaState
{
	//~FollowState() override;
	PookaState* update(InputComponent* input, BaseCharacterComponent *pooka) override;

};

class PlayerState : public PookaState
{
public:
	PlayerState(){};
	~PlayerState() {}
	PookaState* update(InputComponent* input, BaseCharacterComponent *pooka) override {
		UNREFERENCED_PARAMETER(input);
		UNREFERENCED_PARAMETER(pooka);
		if (Changed != nullptr) {
			Changed->Changed = nullptr;
			return Changed;
			//Changed = nullptr;
		}

		return nullptr;
	}

};

