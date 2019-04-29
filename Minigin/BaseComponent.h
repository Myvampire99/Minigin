#pragma once
class GameObject;
class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();//virtual ?
	//Rule of 5 ?


//protected: ??
	dae::GameObject *m_GameObject;
	virtual void Update(float elapsedTime) = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;

};

