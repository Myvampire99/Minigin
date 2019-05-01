#pragma once
#include "MiniginPCH.h"
#include "Minigin.h"
#include "BaseCharacterComponent.h"

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

class JumpCommand : public Command
{
public:
	JumpCommand(dae::Minigin *pointer,bool &Continue)
	{
		m_Pointer = pointer;
		m_Continue =  &Continue;
	}

	dae::Minigin *m_Pointer;
	bool m_Continue;

	void Execute() override {
		m_Pointer->TestFunction(m_Continue);
	}
};

class GoRight : public Command
{
public:
	GoRight(BaseCharacterComponent *p)
		:cp{p}
	{
		
	}

	BaseCharacterComponent *cp;

	void Execute() override {
		cp->Xforward(0.01f, 1);
	}
};

class FartCommand : public Command
{
public:
	virtual void Execute() override {
		std::cout << "FART" << std::endl;
	}
};
//======