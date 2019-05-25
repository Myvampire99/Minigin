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

class FygarFire : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		dynamic_cast<FygarCharacterComponent*>(dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(player)->GetComponent<FygarCharacterComponent>())->BreathFire();
	}
};


class ChangeToPlayerC : public Command
{
public:
	virtual void Execute(int player) override {//TODO: multiple players
		UNREFERENCED_PARAMETER(player);
		dynamic_cast<PookaState*>(dae::Singleton<ServiceLocator>::GetInstance().GetPlayersObject(1)->GetComponent<AIComponent>()->GetState())->ChangeToPlayer();

		//dae::SceneManager::GetInstance().SetSceneActive("CoopLevel", true);
		//dae::SceneManager::GetInstance().SetSceneActive("DigDugLevel", false);
	}
};
//======