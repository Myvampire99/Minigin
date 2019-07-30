#include "MiniginPCH.h"
#include "PengoCharacterComponent.h"


PengoCharacterComponent::PengoCharacterComponent(GridManager* grid)
	:m_GridManager{ grid }
	, m_SpeedBlocks{4.f}
{
}


PengoCharacterComponent::~PengoCharacterComponent()
{
}

void PengoCharacterComponent::Push() {

	GridManager::Node *CurrentNode = m_GridManager->GetClosestNode(m_GameObject->GetPos());
	auto gameobject = std::make_shared<dae::GameObject>();

	if (CurrentNode) {
		switch (m_DirectionState) {
		case Left:
			//If left an other node ===============================================================================================================================================================================================
			//if Has Tag
			if (CurrentNode->Links->left->tag == 1) {
				if (CurrentNode->Links->left->Links->left) {
					if (CurrentNode->Links->left->Links->left->tag != 0) {
						CurrentNode->Links->left->object->MarkForDelete();
						m_GridManager->FreeBlock(CurrentNode->Links->left, gameobject);
					}
					else {
						CurrentNode->Links->left->object->AddComponent(new VelocityComponent{ dae::Vector2{-m_SpeedBlocks,0.f} });
						m_GridManager->LockIfStatic(CurrentNode->Links->left->object);
						gameobject->SetPosition(CurrentNode->Links->left->object->GetPos());
						m_GridManager->FreeBlock(CurrentNode->Links->left, gameobject);
					}
				}
				else {
					CurrentNode->Links->left->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->left, gameobject);
				}
			}
		
			break;
		case Right:
			if (CurrentNode->Links->right->tag == 1) {
				if (CurrentNode->Links->right->Links->right) {
					if (CurrentNode->Links->right->Links->right->tag != 0) {
						CurrentNode->Links->right->object->MarkForDelete();
						m_GridManager->FreeBlock(CurrentNode->Links->right, gameobject);
					}
					else {
						CurrentNode->Links->right->object->AddComponent(new VelocityComponent{ dae::Vector2{m_SpeedBlocks,0.f} });
						m_GridManager->LockIfStatic(CurrentNode->Links->right->object);
						gameobject->SetPosition(CurrentNode->Links->right->object->GetPos());
						m_GridManager->FreeBlock(CurrentNode->Links->right, gameobject);
					}
				}
				else {
					CurrentNode->Links->right->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->right, gameobject);
				}
			}
			break;
		case Down:
			if (CurrentNode->Links->down->tag == 1) {
				if (CurrentNode->Links->down->Links->down) {
					if (CurrentNode->Links->down->Links->down->tag != 0) {
						CurrentNode->Links->down->object->MarkForDelete();
						m_GridManager->FreeBlock(CurrentNode->Links->down, gameobject);
					}
					else {
						CurrentNode->Links->down->object->AddComponent(new VelocityComponent{ dae::Vector2{0.f,m_SpeedBlocks} });
						m_GridManager->LockIfStatic(CurrentNode->Links->down->object);
						gameobject->SetPosition(CurrentNode->Links->down->object->GetPos());
						m_GridManager->FreeBlock(CurrentNode->Links->down, gameobject);
					}
				}
				else {
					CurrentNode->Links->down->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->down, gameobject);
				}
			}
			break;
		case Up:
			if (CurrentNode->Links->up->tag == 1) {
				if (CurrentNode->Links->up->Links->up) {
					if (CurrentNode->Links->up->Links->up->tag != 0) {
						CurrentNode->Links->up->object->MarkForDelete();
						m_GridManager->FreeBlock(CurrentNode->Links->up, gameobject);
					}
					else {
						CurrentNode->Links->up->object->AddComponent(new VelocityComponent{ dae::Vector2{0.f,-m_SpeedBlocks} });
						m_GridManager->LockIfStatic(CurrentNode->Links->up->object);
						gameobject->SetPosition(CurrentNode->Links->up->object->GetPos());
						m_GridManager->FreeBlock(CurrentNode->Links->up, gameobject);
					}
				}
				else {
					CurrentNode->Links->up->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->up, gameobject);
				}
			}
			break;
		default:;
		}
	}




}

void PengoCharacterComponent::localIni() {
	//TODO: Contoll hardcoded
	dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(4), new PlayerPush(), m_Input->GetPlayerID(),true);
}

void PengoCharacterComponent::LocalUpdate(float elapsedTime)  {
	UNREFERENCED_PARAMETER(elapsedTime);
	if (m_GameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions().size() > 0) {
		for (auto col : m_GameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions()) {
			if (col) {
				if (col->GetComponent()->m_GameObject->GetComponent<SnoBeeComponent>()) {
					if (!m_reset) {
						m_reset = true;
						dae::Singleton<ServiceLocator>::GetInstance().SetHealth(dae::Singleton<ServiceLocator>::GetInstance().GetHealth() - 1);
						if (dae::Singleton<ServiceLocator>::GetInstance().GetHealth() < 0)
							dae::Singleton<dae::SceneManager>::GetInstance().ResetActiveScene();
						else {
							m_GameObject->SetPosition(64.f, 64.f);
						}
					}
					else {
						m_reset = false;
					}
				}
			}
		}
	}
}