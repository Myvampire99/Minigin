#pragma once
#include "MiniginPCH.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute() = 0;
};


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

class PlayerFire : public Command
{
public:
	virtual void Execute() override {//TODO: multiple players
		dynamic_cast<DiggerCharacterComponent*>(dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(0)->GetComponent<BaseCharacterComponent>())->Fire();
	}
};
//======