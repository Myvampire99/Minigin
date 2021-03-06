#pragma once
#include "LevelObject.h"
class GridLevel : public BaseComponent
{
public:
	GridLevel(int m_Width, int m_Height, float blockSize, dae::Vector2 m_Position, dae::Vector2 offset = {});
	~GridLevel();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;



private:
	void RemoveBlock(int ID);

	int m_Width;
	int m_Height;
	float m_BlockSize;
	dae::Vector2 m_Position;

	std::vector<LevelObject*> m_Objects;

	float ClosestDistanceToRoundValue(float value);
	dae::Vector2 GetClosestPointViaPos(dae::Vector2 pos);

	//Only values between 0 - 1
	dae::Vector2 GetClosestPosOnLineInSquare(dae::Vector2 pos, int ID);

	dae::Vector2 m_Offset;
	std::map<LevelObject*, dae::Vector2> m_FreeBlocks;

	
public:
	int GetClosestIDViaPos(dae::Vector2 pos) const;
	void ChangeBlock(LevelObject* object, dae::Vector2 posInGrid);
	void ChangeBlock(LevelObject* object, int id);
	void AddBlock(LevelObject* object, int id);
	void FillLevel(LevelObject* object);

	dae::Vector2 GetClosestPosOnLine(const dae::Vector2 &currentPos);

	void FreeBlock(LevelObject* freedBlock, LevelObject* replacment);
	void LockBlock(LevelObject* lockBlock, int ID);
	void SetPositionFreeBlock(LevelObject* freedBlock, dae::Vector2 pos);
	dae::Vector2 GetPositionFreeBlock(LevelObject* freedBlock);

	float GetBlockSize();

	void SetWalkable(int ID,bool IsWalkable);
	bool IsWalkable(int ID);
	std::pair<bool,dae::Vector2> IsInNotWalkable(dae::Vector2 pos, dae::Vector2 WH = {0,0});

	enum Dir {
		Center = 0,
		Left,
		Right,
		Up,
		Down
	};

	dae::Vector2 GetPosFromID(int ID);
	LevelObject* GetObjectWithID(int ID, Dir dir = Center);
	LevelObject* GetObjectWithPos(dae::Vector2 pos);


	int GetWidth();
	int GetHeight();

	int GetID(const LevelObject* object)const;

	void SetOffset(dae::Vector2 offset);

	bool InsideBounds(unsigned int ID);
};

