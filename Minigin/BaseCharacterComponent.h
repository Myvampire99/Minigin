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
	void Xforward( int direction);
	void Yforward( int direction);
protected:
	virtual void LocalUpdate(const float elapsedTime);
private:

	float m_Speed;
	InputComponent* m_Input;
	int	Xleft, Xright, Yup, Ydown;
	
};

