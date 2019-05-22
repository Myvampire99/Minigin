#pragma once
#include "InputManager.h"

class WanderingState;
class FollowState;
class PlayerState;

class PookaState
{
public:
	//virtual ~PookaState();
	virtual void update(InputComponent* input, PookaCharacterComponent *pooka) { UNREFERENCED_PARAMETER(input); UNREFERENCED_PARAMETER(pooka);
	};

	static WanderingState wandering;
	//static FollowState follow;
	//static PlayerState state;
	int player = 1;
};

class WanderingState : public PookaState
{
	WanderingState() : m_CurrentDir() {};
	~WanderingState()  {}
	void update(InputComponent* input, PookaCharacterComponent *pooka) override
	{
		auto dir = pooka->GetEmptyDir();

		//TODO: Ugly Code
		if (dir.left && m_CurrentDir.left) {
			dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xleft), player);
			m_CurrentDir.rem();
			m_CurrentDir.left = dir.left;
			return;
		}
		
		if (dir.up && m_CurrentDir.up) {
			dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Yup), player);
			m_CurrentDir.rem();
			m_CurrentDir.up = dir.up;
			return;
		}

		if (dir.right && m_CurrentDir.right) {
			dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xright), player);
			m_CurrentDir.rem();
			m_CurrentDir.right = dir.right;
			return;
		}

		if (dir.down && m_CurrentDir.down) {
			dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Ydown), player);
			m_CurrentDir.rem();
			m_CurrentDir.down = dir.down;
			return;
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
				return;
			}

			if (dir.left&& randomint ==1) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xleft), player);
				m_CurrentDir.rem();
				m_CurrentDir.left = dir.left;
				return;
			}

			if (dir.down&& randomint == 2) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Ydown), player);
				m_CurrentDir.rem();
				m_CurrentDir.down = dir.down;
				return;
			}

			if (dir.right&& randomint == 3) {
				dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(pooka->Xright), player);
				m_CurrentDir.rem();
				m_CurrentDir.right = dir.right;
				return;
			}
		}


						

	}
private:
	PookaCharacterComponent::EmptyDir m_CurrentDir;

};

class FollowState : public PookaState
{
	//~FollowState() override;
	void update(InputComponent* input, PookaCharacterComponent *pooka) override;

};

class PlayerState : public PookaState
{
	//~PlayerState() override;
	void update(InputComponent* input, PookaCharacterComponent *pooka) override;

};

