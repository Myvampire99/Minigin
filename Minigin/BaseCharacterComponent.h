#pragma once
#include "BaseComponent.h"

class InputComponent;
class BaseCharacterComponent : public BaseComponent
{
public:
	BaseCharacterComponent();
	~BaseCharacterComponent();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

	void SetSpeed(float speed);
	void AssignButton(int XLEFT, int XRIGHT, int YUP, int YDOWN);


//private:
	void Xforward(const float elapsedTime, int direction);
	void Yforward(const float elapsedTime, int direction);
private:

	float m_Speed;
	InputComponent* m_Input;
	int	Xleft, Xright, Yup, Ydown;
	
};

