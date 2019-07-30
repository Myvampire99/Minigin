#include "MiniginPCH.h"
#include "AIStateComponent.h"


AIStateComponent::AIStateComponent(GridManager* grid,int player)
	: m_MaxSpawnSeconds{2.5f}
	, m_ElapsedSpawnSeconds{}
	, m_GridManager{ grid }
	, m_PlayerID{ player }
	, m_AIState{ SpawnState }
	, m_NodeSpace{1.f}
	, m_Score{400}
{
}


AIStateComponent::~AIStateComponent()
{
}

void AIStateComponent::SetPlayer(bool isplayer) {
	IsAI = !isplayer;
}


bool AIStateComponent::IsHarmless() {
	if (m_AIState == SpawnState)
		return true;
	else
		return false;
}

void AIStateComponent::Update(const float elapsedTime) {

	switch (m_AIState) {
	case SpawnState:

		if (m_ElapsedSpawnSeconds == 0) {
			if (!m_GameObject->GetComponent<dae::SpriteComponent>()) {
				dae::Sprite* sprite = new dae::Sprite("Resources/Sprites/SlimeSpawn.png", 1, 5, 5, 0.5f);
				m_GameObject->AddComponent(new dae::SpriteComponent(0, sprite));
			}
		}
	
		m_ElapsedSpawnSeconds += elapsedTime;
		if (m_MaxSpawnSeconds < m_ElapsedSpawnSeconds) {
			m_AIState = WalkingState;
			m_GameObject->RemoveComponent<dae::SpriteComponent>();
			dae::Sprite* sprite = new dae::Sprite("Resources/Sprites/WalkingSlime.png", 1,2, 2, 1.f);
			m_GameObject->AddComponent(new dae::SpriteComponent(0, sprite));
			m_ElapsedSpawnSeconds = 0;
		}

		break;
	case DeadState:
		dae::Singleton<ServiceLocator>::GetInstance().SetCurrentScore(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore() + m_Score);
		m_GameObject->MarkForDelete();
		//m_GameObject->SetEnabled(false);
		m_AIState = SpawnState;

		break;
	case DecidingDirectionState:
		if (IsAI) {
			m_Direction = AiControlWalking();
			if(m_AIState == DecidingDirectionState)
				m_AIState = WalkingState;
		}
		CheckIfHit();
		break;
	case WalkingState:

		if(WalkUntilNextNode())
			m_AIState = DecidingDirectionState;

		CheckIfHit();
		break;
	case BlockDestroyState:
		m_GameObject->GetComponent<SnoBeeComponent>()->BreakBlock();
		m_AIState = DecidingDirectionState;
		CheckIfHit();
		break;
	default:
		break;
	}




}

void AIStateComponent::onNotify(Event event) {

	if(Event::EVENT_PLAYER_DEAD == event)
		m_AIState = SpawnState;

}

void AIStateComponent::CheckIfHit() {
	if (m_GameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions().size() > 0) {
		for (auto col : m_GameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions()) {
			if (col->GetComponent()->m_GameObject->GetComponent<VelocityComponent>()) {
				m_AIState = DeadState;
			}
		}
	}
}

bool AIStateComponent::WalkUntilNextNode() {

	InputComponent* input = m_GameObject->GetComponent<InputComponent>();
	BaseCharacterComponent* SnoBee = m_GameObject->GetComponent<BaseCharacterComponent>();

	switch (m_Direction) {
	case 0:
		 dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(SnoBee->Xleft), m_PlayerID);
		break;
	case 1:
		 dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(SnoBee->Xright), m_PlayerID);
		break;
	case 2:
		 dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(SnoBee->Yup), m_PlayerID);
		break;
	case 3:
		 dae::Singleton<InputManager>::GetInstance().ForceButton(input->GetButton(SnoBee->Ydown), m_PlayerID);
		break;
	}

	if (m_GridManager->GetClosestNode(m_GameObject->GetPos())->object->GetPos().DistanceTo(m_GameObject->GetPos()) < m_NodeSpace)
		return true;
	else
		return false;

}

int AIStateComponent::AiControlWalking() {

	GridManager::Node* currentNode = m_GridManager->GetClosestNode(m_GameObject->GetPos());

	int dirToGo{};
	bool valid = false;
	m_PrevDirection = m_Direction;
	for (int i{}; i < 4; ++i) {
		if (ChooseDirecion(i, currentNode) != -1) {
			dirToGo++;
			if (m_PrevDirection == i)
				valid = true;
		}
	}
	if (dirToGo < 3 && valid)
		return m_Direction;

	int Direction = rand() % 4;

	int returnValue = ChooseDirecion(Direction, currentNode);
	if (returnValue != -1)
		return returnValue;

	for (int i{}; i < 4; ++i) {
		returnValue = ChooseDirecion(i, currentNode);
		if (returnValue != -1)
			return returnValue;
		if ((rand() % 2) == 1) {
			m_AIState = BlockDestroyState;
			return i;
		}
	}

	return -1;
}

int AIStateComponent::ChooseDirecion(int d, GridManager::Node* currentNode) {

	switch (d) {
	case 0:
		if (currentNode->Links->left)
			if (currentNode->Links->left->tag == 0)
				return 0;
		break;
	case 1:
		if (currentNode->Links->right)
			if (currentNode->Links->right->tag == 0)
				return 1; 
		break;
	case 2:
		if (currentNode->Links->up)
			if (currentNode->Links->up->tag == 0)
				return 2; 
		break;
	case 3:
		if (currentNode->Links->down)
			if (currentNode->Links->down->tag == 0)
				return 3;
		break;
	}

	return -1;

}


void AIStateComponent::Draw() {}
void AIStateComponent::Initialize()  {}