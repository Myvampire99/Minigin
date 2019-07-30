#include "MiniginPCH.h"
#include "SnoBeeComponent.h"


SnoBeeComponent::SnoBeeComponent(GridManager* grid)
	:m_GridManager{grid}
{
}


SnoBeeComponent::~SnoBeeComponent()
{
}

void SnoBeeComponent::LocalUpdate(const float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
		//TODO: Contoll hardcoded and in update
	dae::Singleton<InputManager>::GetInstance().AssignButton(m_Input->GetButton(4), new SnooBeeDestroy(), m_Input->GetPlayerID(), true);

}

void SnoBeeComponent::BreakBlock() {
	GridManager::Node *CurrentNode = m_GridManager->GetClosestNode(m_GameObject->GetPos());
	auto gameobject = std::make_shared<dae::GameObject>();

	if (CurrentNode) {
		switch (m_DirectionState) {
		case Left:
			if (CurrentNode->Links->left->tag == 1) {
					CurrentNode->Links->left->object->MarkForDelete();
					//m_GridManager->GetNode()
					m_GridManager->FreeBlock(CurrentNode->Links->left, gameobject);
			}
			break;
		case Right:
			if (CurrentNode->Links->right->tag == 1) {
					CurrentNode->Links->right->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->right, gameobject);
			}
			break;
		case Down:
			if (CurrentNode->Links->down->tag == 1) {
					CurrentNode->Links->down->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->down, gameobject);
			}
			break;
		case Up:
			if (CurrentNode->Links->up->tag == 1) {
					CurrentNode->Links->up->object->MarkForDelete();
					m_GridManager->FreeBlock(CurrentNode->Links->up, gameobject);
			}
			break;
		default:;
		}
	}
}