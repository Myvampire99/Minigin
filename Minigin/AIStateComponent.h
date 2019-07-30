#pragma once
class AIStateComponent : public BaseComponent
{
public:
	AIStateComponent(GridManager* grid,int player);
	~AIStateComponent();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

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

	float m_MaxSpawnSeconds;
	float m_ElapsedSpawnSeconds;

	bool IsAI = true;

	float m_NodeSpace;

	int AiControlWalking();
	int ChooseDirecion(int d,  GridManager::Node* currentNode);
	bool WalkUntilNextNode();

	int m_PlayerID;
	int m_Direction;
	int m_PrevDirection;
	int m_Score;
};

