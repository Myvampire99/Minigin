#include "MiniginPCH.h"
#include "GridManager.h"


GridManager::GridManager()
:m_Margin{}
, m_Row{}, m_Column{}
{
}


GridManager::~GridManager()
{
	for (int i{}; i < (int)m_Nodes.size(); i++) {
		
		delete m_Nodes[i]->Links;
		delete m_Nodes[i];
	}

}

void GridManager::CreateRectGrid(dae::Scene *scene,int width, int height, float margin) {

	m_Margin = margin;
	m_Row = width;
	m_Column = height;

	for (int i{}; i < height; i++) {
		for (int j{}; j < width; j++) {

			Node *node = new Node{};
			node->object = std::make_shared<dae::GameObject>();
			node->object->SetPosition(j*margin,i*margin);
			scene->Add(node->object);
			node->ID = (i+1) * (j+1);
			m_Nodes.push_back(node);

		}
	}

	int counter{};
	Node *down = nullptr;
	Node *up = nullptr;
	Node *left = nullptr;
	Node *right = nullptr;

	for (int i{}; i < height; ++i) {
		for (int j{}; j < width; ++j) {


			if (i != height - 1)
				down = m_Nodes[counter + width];
			else
				down = nullptr;

			if(i != 0)
				up = m_Nodes[counter - width];
			else
				up = nullptr;

			if (j != 0)
				left = m_Nodes[counter - 1];
			else
				left = nullptr;

			if (j != width - 1)
				right = m_Nodes[counter + 1];
			else
				right = nullptr;


			m_Nodes[counter]->Links = new Link();
			m_Nodes[counter]->Links->down = down;
			m_Nodes[counter]->Links->up = up;
			m_Nodes[counter]->Links->right = right;
			m_Nodes[counter]->Links->left = left;
			
				

			counter++;
		}
	}


}

//if ID = -1 -> all components
//TEMPLATE
void GridManager::AddComponents(BaseComponent *comp, int ID) {

	if (ID > -1) {
			m_Nodes[ID]->object->AddComponent(comp);
	}

}

//void GridManager::DebugUpdate(dae::Vector2 pos) {
//	
//	
//
//}

GridManager::Node* GridManager::GetNode(int ID) {

	return m_Nodes[ID];
}

GridManager::Node* GridManager::GetNode(std::shared_ptr<dae::GameObject> object) {

	for (auto Node : m_Nodes) {
		if (Node->object == object) {
			return Node;
		}
	}

	return nullptr;
}

GridManager::Node* GridManager::GetClosestNode(dae::Vector2 pos) {

	float shortest{ 99999.f };
	float current{ 0.f };
	Node *returningNode = nullptr;

	for (auto Node : m_Nodes) {
		current = Node->object->GetPos().DistanceTo(pos);
		if (shortest > current) {
			shortest = current;
			returningNode = Node;
		}
	}

	return returningNode;
}


void GridManager::FreeBlock(Node* blockToFree, std::shared_ptr<dae::GameObject> replacement) {


	Node* rep = GetNode(blockToFree->object);
	rep->tag = 0;
	replacement->SetPosition(rep->object->GetPos());
	rep->object = replacement;

	//if (replacement->Links->up)
	//	replacement->Links->up->Links->down = replacement;
	//if (replacement->Links->down)
	//	replacement->Links->down->Links->up = replacement;
	//if (replacement->Links->left)
	//	replacement->Links->left->Links->right = replacement;
	//if (replacement->Links->right)
	//	replacement->Links->right->Links->left = replacement;


}

void GridManager::LockIfStatic(std::shared_ptr<dae::GameObject> LockBlock) {
	m_LockIfStatic.push_back(LockBlock);
}

void GridManager::Update(float elapsedTime) {

	//for (int i{1};i<(int)m_Nodes.size();++i){

	//	DD::GetInstance().DrawLine(m_Nodes[i]->object->GetPos(), m_Nodes[i - 1]->object->GetPos());
	//}
	




	UNREFERENCED_PARAMETER(elapsedTime);
	std::vector<std::shared_ptr<dae::GameObject>> markForDeletion;

	if (m_LockIfStatic.size() > 0) {
		for (auto block : m_LockIfStatic) {
			if (block->GetComponent<VelocityComponent>()) {
				if (block->GetComponent<VelocityComponent>()->GetVelocity() == dae::Vector2{ 0.f,0.f }) {
					
					
					block->SetPosition(GetClosestNode(block->GetPos())->object->GetPos());
					//block->SetPosition(dae::Vector2{ m_Column%GetClosestNode(block->GetPos())->ID)  m_Margin, m_Row*m_Margin });
					
					
					GetClosestNode(block->GetPos())->object->MarkForDelete();
					GetClosestNode(block->GetPos())->object = block;
					block->RemoveComponent<VelocityComponent>();
					markForDeletion.push_back(block);

					GetNode(block)->tag = 1;
				}
			}
		}
	}
	else {
	}

	if (markForDeletion.size() > 0) {
		for (auto deletion : markForDeletion) {
			for (int i{}; i < (int)m_LockIfStatic.size(); ++i) {
				if (m_LockIfStatic[i] == deletion) {
					m_LockIfStatic.erase(m_LockIfStatic.begin() + i);
					break;
				}
			}
		}
	
	}


}



std::vector<float> GridManager::GetAllColumnsX() {
	std::vector<float> column;

	for (int i{}; i < m_Column; ++i) {
		column.push_back(m_Nodes[i]->object->GetPos().x);
	}

	return column;
}

std::vector<float> GridManager::GetAllRowsY() {
	std::vector<float> column;

	for (int i{}; i < m_Row; ++i) {
		column.push_back(m_Nodes[i*m_Row]->object->GetPos().y);
	}

	return column;
}
