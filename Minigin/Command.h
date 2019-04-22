#pragma once
#include "MiniginPCH.h"
#include "Minigin.h"

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
class FireCommand : public Command
{
public:
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

class DuckCommand : public Command
{
public:
	void Execute() override {
		std::cout << "DUCK" << std::endl;
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