#pragma once
#include "LevelObject.h"
class GridLevel : public BaseComponent
{
public:
	GridLevel(int m_Width,int m_Height,float blockSize,dae::Vector2 m_Position);
	~GridLevel();

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

private:
	int m_Width;
	int m_Height;
	float m_BlockSize;
	dae::Vector2 m_Position;

	std::vector<LevelObject*> m_Objects;

	float ClosestDistanceToRoundValue(float value);
	dae::Vector2 GetClosestPointViaPos(dae::Vector2 pos);


	//Only values between 0 - 1
	dae::Vector2 GetClosestPosOnLineInSquare(dae::Vector2 pos, int ID);
public:
	int GetClosestIDViaPos(dae::Vector2 pos) const;
	void ChangeBlock(LevelObject* object, dae::Vector2 posInGrid);
	void ChangeBlock(LevelObject* object, int id);
	void AddBlock(LevelObject* object, int id);
	void FillLevel(LevelObject* object);

	dae::Vector2 GetClosestPosOnLine(const dae::Vector2 &currentPos);

	dae::Vector2 GetPosFromID(int ID);
	LevelObject* GetObjectWithID(int ID);
	LevelObject* GetObjectWithPos(dae::Vector2 pos);

	int GetWidth();
	int GetHeight();

	int GetID(const LevelObject* object)const;
};
