#pragma once
#include "BaseComponent.h"

class InputComponent;
class BaseCharacterComponent : public BaseComponent
{
public:
	BaseCharacterComponent();
	~BaseCharacterComponent();

	void Update(const float elapsedTime) override;
	virtual void Draw();
	void Initialize() override;

	void SetSpeed(float speed);
	void AssignButton(int XLEFT, int XRIGHT, int YUP, int YDOWN);

//private:
	void Xforward( int direction);
	void Yforward( int direction);
protected:
	virtual void LocalUpdate(const float elapsedTime);
	InputComponent* m_Input;
	virtual void localIni();
	bool ForceStop;
private:

	float m_Speed;
	int	Xleft, Xright, Yup, Ydown;
	
};

