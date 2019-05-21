#pragma once
#include "MiniginPCH.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute(int player) = 0;
};


class PlayerUp : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(player)->GetComponent<BaseCharacterComponent>()->Yforward(-1);
	}
};

class PlayerDown : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(player)->GetComponent<BaseCharacterComponent>()->Yforward(1);
	}
};

class PlayerLeft : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(player)->GetComponent<BaseCharacterComponent>()->Xforward(-1);
	}
};

class PlayerRight : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(player)->GetComponent<BaseCharacterComponent>()->Xforward(1);
	}
};

class PlayerFire : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		dynamic_cast<DiggerCharacterComponent*>(dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(player)->GetComponent<BaseCharacterComponent>())->Fire();
	}
};
//======