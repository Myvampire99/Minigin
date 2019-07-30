#include "MiniginPCH.h"
#include "MazeGenerator.h"


MazeGenerator::MazeGenerator()
{
}


MazeGenerator::~MazeGenerator()
{
}

std::vector<int> MazeGenerator::CreateMaze(int height, int width) {

	srand((unsigned)time(NULL));

	std::vector<MazeGenerator::Node*> Nodes;
	for (int i{}; i < height*width; ++i) {
		Nodes.push_back(new MazeGenerator::Node());
	}

	CreateLinks(height,width, Nodes);




	int counter{};
	int prev{-1};
	std::vector<MazeGenerator::Node*> Path;
	Path.push_back(Nodes[0]);
	Path[0]->tag = 1;

	while (counter != -1) {

		int nr = rand() % 4;
		bool found = false;

		if (Path[counter]->links[nr]) {
			if (Path[counter]->links[nr]->tag == 0) {
				Path[counter]->tag = 1;
				Path[counter]->links[nr]->tag = 1;
				Path.push_back(Path[counter]->links[nr]);
				found = true;
				counter = Path.size() -2;//TODO: begone!
			}
			else {
				for (int i{}; i < 4; ++i) {
					if (Path[counter]->links[i]) {
						if (Path[counter]->links[i]->tag == 0) {
							Path[counter]->tag = 1;
							Path[counter]->links[i]->tag = 1;
							Path.push_back(Path[counter]->links[i]);
							found = true;
							nr = i;
							counter = Path.size() - 2;//TODO: begone!
							break;
						}
					}
				}
			}
		}
		else {
			
			for (int i{}; i < 4; ++i) {
				if (Path[counter]->links[i]) {
					if (Path[counter]->links[i]->tag == 0) {
						Path[counter]->tag = 1;
						Path[counter]->links[i]->tag = 1;
						Path.push_back(Path[counter]->links[i]);
						found = true;
						nr = i;
						counter = Path.size() -2;//TODO: begone!
						break;
					}
				}
			}
		}

		if (!found) {
			counter--;
		}
		else {
			//if(counter != 0 )
				CreateWall(Path[counter],prev, nr);
			++counter;
		}
		
		//backtracking
		prev = nr;

	}


	std::vector<int> returning;
	for (auto node : Nodes) {
		returning.push_back(node->tag);
	}

	return returning;

}

//for (int i{}; i < 4; ++i) {
//	if (Path[i]->links[nr]) {
//		if (Path[i]->links[nr]->tag == 0) {
//			Path[counter]->tag = 1;
//			Path.push_back(Path[i]->links[nr]);
//			found = true;
//			break;
//		}
//	}
//}

void MazeGenerator::CreateWall(MazeGenerator::Node *PrevNode, int previousDirection, int currentDirection) {

	if (previousDirection == -1) {
		previousDirection = currentDirection;
	}
	else {

		if (previousDirection == currentDirection) {

			if (PrevNode->links[(currentDirection + 1) % 4])
				if (PrevNode->links[(currentDirection + 1) % 4]->tag == 0)
					PrevNode->links[(currentDirection + 1) % 4]->tag = 2;

			if (currentDirection != 0) {
				if (PrevNode->links[(currentDirection - 1) % 4])
					if (PrevNode->links[(currentDirection - 1) % 4]->tag == 0)
						PrevNode->links[(currentDirection - 1) % 4]->tag = 2;
			}
			else {
				if (PrevNode->links[3])
					if (PrevNode->links[3]->tag == 0)
						PrevNode->links[3]->tag = 2;
			}


		}
		else {
			if(PrevNode->links[currentDirection])//TODO: begone!
			if (PrevNode->links[currentDirection]->links[(previousDirection + 2)%4 ])
				if (PrevNode->links[currentDirection]->links[(previousDirection + 2) % 4]->tag == 0)
					PrevNode->links[currentDirection]->links[(previousDirection + 2) % 4]->tag = 2;
		}
	}
}


void MazeGenerator::CreateLinks(int height, int width, std::vector<MazeGenerator::Node *> &Nodes) {

	int counter{};
	Node *down = nullptr;
	Node *up = nullptr;
	Node *left = nullptr;
	Node *right = nullptr;

	for (int i{}; i < height; ++i) {
		for (int j{}; j < width; ++j) {


			if (i != height - 1)
				down = Nodes[counter + width];
			else
				down = nullptr;

			if (i != 0)
				up = Nodes[counter - width];
			else
				up = nullptr;

			if (j != 0)
				left = Nodes[counter - 1];
			else
				left = nullptr;

			if (j != width - 1)
				right = Nodes[counter + 1];
			else
				right = nullptr;

			Nodes[counter]->links[0] = down;
			Nodes[counter]->links[2] = up;
			Nodes[counter]->links[3] = left;
			Nodes[counter]->links[1] = right;


			counter++;
		}
	}

}