#pragma once
#include "MiniginPCH.h"
///#include "Minigin.h"
//#include "BaseCharacterComponent.h"
//#include "Singleton.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute() = 0;
};


//====
//TODO: Remove
//Dummy Classes
//====
class MoveX : public Command
{
public:
	//MoveX(BaseCharacterComponent)

	void Execute() override { std::cout << "FIRE" << std::endl; }
};

//class JumpCommand : public Command
//{
//public:
//	JumpCommand(dae::Minigin *pointer,bool &Continue)
//	{
//		m_Pointer = pointer;
//		m_Continue =  &Continue;
//	}
//
//	dae::Minigin *m_Pointer;
//	bool m_Continue;
//
//	void Execute() override {
//		m_Pointer->TestFunction(m_Continue);
//	}
//};

//class GoRight : public Command
//{
//public:
//	GoRight(BaseCharacterComponent *p)
//		:cp{p}
//	{
//		
//	}
//
//	BaseCharacterComponent *cp;
//
//	void Execute() override {
//		cp->Xforward(0.01f, 1);
//	}
//};
//
//class GoUp : public Command
//{
//public:
//	GoUp(BaseCharacterComponent *p)
//		:cp{ p }
//	{
//
//	}
//
//	BaseCharacterComponent *cp;
//
//	void Execute() override {
//		cp->Yforward(0.01f, 1);
//	}
//};

//class ServiceLocator;
//class BaseCharacterComponent;
class PlayerUp : public Command
{
public:
	virtual void Execute() override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(0)->GetComponent<BaseCharacterComponent>()->Yforward(-1);
	}
};

class PlayerDown : public Command
{
public:
	virtual void Execute() override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(0)->GetComponent<BaseCharacterComponent>()->Yforward(1);
	}
};

class PlayerLeft : public Command
{
public:
	virtual void Execute() override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(0)->GetComponent<BaseCharacterComponent>()->Xforward(-1);
	}
};

class PlayerRight : public Command
{
public:
	virtual void Execute() override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(0)->GetComponent<BaseCharacterComponent>()->Xforward(1);
	}
};
//======