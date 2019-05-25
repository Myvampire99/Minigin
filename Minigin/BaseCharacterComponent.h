#pragma once
#include "BaseComponent.h"

class InputComponent;
class BaseCharacterComponent : public BaseComponent
{
public:
	BaseCharacterComponent();
	~BaseCharacterComponent();
	dae::GameObject* GetGameObject();

	void Update(const float elapsedTime) override;
	virtual void Draw();
	void Initialize() override;

	//void SetSpeed(float speed);
	void AssignButton(int XLEFT, int XRIGHT, int YUP, int YDOWN);

	//Gets vertical flip and horizonal flip
	std::pair<bool, bool> GetFlipVertnFlipHor();

	enum Direction {
		Up,
		Right,
		Left,
		Down,
		Idle
	};

	Direction GetDirection();
	
	void Xforward( int direction);
	void Yforward( int direction);
protected:
	Direction DirectionWithoutIdle;

	Direction m_DirectionState;
	virtual void LocalUpdate(const float elapsedTime);
	InputComponent* m_Input;
	virtual void localIni();
	bool ForceStop;
private:

	float m_Speed;
public:
	int	Xleft, Xright, Yup, Ydown;


};

