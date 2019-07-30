#pragma once
class MazeGenerator
{
public:
	MazeGenerator();
	~MazeGenerator();

	std::vector<int> CreateMaze(int height,int width);

private:

	struct Node {
		int tag{ 0 };
		MazeGenerator::Node *links[4];
	};

	void CreateLinks(int height, int width, std::vector<MazeGenerator::Node *> &Nodes);
	void CreateWall(MazeGenerator::Node *PrevNode,int previousDirection,int currentDirection);
};

