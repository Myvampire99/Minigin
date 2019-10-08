#pragma once
class AIStateComponent : public BaseComponent,public Observer
{
public:
	AIStateComponent(GridManager* grid,int player);
	~AIStateComponent();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

	bool IsHarmless();

	void SetPlayer(bool isplayer = true);

	//Thread Purp
	bool IsOnThread = false;
private:
	enum AIState {
		SpawnState,
		WalkingState,
		BlockDestroyState,
		DeadState,
		DecidingDirectionState
	};
	AIState m_AIState;

	GridManager* m_GridManager;


	void CheckIfHit();
	float m_ElapsedSpawnSeconds;
	float m_MaxSpawnSeconds;

	bool IsAI = true;

	float m_NodeSpace;

	int AiControlWalking();
	int ChooseDirecion(int d,  GridManager::Node* currentNode);
	bool WalkUntilNextNode();

	int m_PlayerID;
	int m_Direction;
	int m_PrevDirection;
	int m_Score;


	void onNotify(Event event) override;
};

