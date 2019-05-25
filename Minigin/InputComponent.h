#pragma once
#include "BaseComponent.h"
class InputComponent : public BaseComponent
{
public:
	InputComponent(int playerid);
	~InputComponent();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

	void AssignButton(int ID, ControllerButton button);
	ControllerButton GetButton(int ID);
	bool NeedUpdate();

	int GetPlayerID();
private:
	std::map<int, ControllerButton> m_Input;
	bool m_NeedUpdate;
	bool m_ResetUpdate;
	int playerID;
};

