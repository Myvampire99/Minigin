#pragma once
//must have an offset from 0.0
class GridManager
{
public:

	struct Link;
	struct Node {
		std::shared_ptr<dae::GameObject> object = nullptr;
		Link *Links;
		int tag{0};
		int ID{ -1 };
	};	
	struct Link {
		Node *left = nullptr;
		Node *right = nullptr;
		Node *up = nullptr;
		Node *down = nullptr;
	};

	float m_Margin;
	int m_Row, m_Column;

	std::vector<Node*> m_Nodes;
	void CreateRectGrid(dae::Scene *scene,int width,int height,float margin);

	void Update(float elapsedTime);

	//void DebugUpdate(dae::Vector2 pos);
	void AddComponents(BaseComponent *comp,int ID = -1);
	Node* GetNode(std::shared_ptr<dae::GameObject> object);
	Node* GetNode(int ID);

	Node* GetClosestNode(dae::Vector2 pos);

	void FreeBlock(Node* blockToFree, std::shared_ptr<dae::GameObject> replacement);
	void LockIfStatic(std::shared_ptr<dae::GameObject> LockBlock);

	std::vector<std::shared_ptr<dae::GameObject>> m_LockIfStatic;

	std::vector<float> GetAllColumnsX();
	std::vector<float> GetAllRowsY();

	GridManager();
	~GridManager();
};

