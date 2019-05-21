#include "MiniginPCH.h"
#include "GridLevel.h"


GridLevel::GridLevel(int m_Width, int m_Height,float blockSize,dae::Vector2 m_Position,dae::Vector2 offset)
	:m_Width{ m_Width }
	, m_Height{ m_Height }
	, m_Position{ m_Position }
	, m_BlockSize{ blockSize }
	, m_Offset{ offset }
{}

GridLevel::~GridLevel()
{}

//const LevelObject* GetType

void GridLevel::SetWalkable(int ID, bool IsWalkable) {
	m_Objects[ID]->SetWalkable(IsWalkable);
}

bool  GridLevel::IsWalkable(int ID) {
	return m_Objects[ID]->IsWalkable();
}

void GridLevel::ChangeBlock(LevelObject* object, dae::Vector2 posInGrid) {
	int id = int(posInGrid.x+posInGrid.y*m_Width);
	ChangeBlock(object, id);
}


std::pair<bool, dae::Vector2>  GridLevel::IsInNotWalkable(dae::Vector2 pos, dae::Vector2 WH) {
	//TODO: pos not over all objects
	int ID = GetClosestIDViaPos(pos);

	/*if (WH.x == 0.f && WH.y == 0.f)
		return std::make_pair<bool, dae::Vector2>(!m_Objects[ID]->IsWalkable(), {});*/

	UNREFERENCED_PARAMETER(WH);
	UNREFERENCED_PARAMETER(ID);

	//if (!m_Objects[GetClosestIDViaPos(pos)]->IsWalkable())
	//	return std::make_pair<bool, dae::Vector2>(true, );
	//if (!m_Objects[GetClosestIDViaPos({pos .x + WH.x,pos.y})]->IsWalkable())//&& GetClosestIDViaPos({ pos.x + WH.x,pos.y }) == ID
	//	return true;
	//if (!m_Objects[GetClosestIDViaPos({ pos.x + WH.x,pos.y + WH.y })]->IsWalkable() )
	//	return true;
	//if (!m_Objects[GetClosestIDViaPos({ pos.x ,pos.y + WH.y })]->IsWalkable())
	//	return true;

	return std::make_pair<bool, dae::Vector2>(false, {0.f,0.f});

}

void GridLevel::ChangeBlock(LevelObject* object, int id) {
	//auto obj = new LevelObject(*object);
	object->SetPos(m_Objects[id]->GetPos());
	m_Objects[id] = object;
	//TODO: delete block
}

void GridLevel::AddBlock(LevelObject* object, int id) {

	auto obj = new LevelObject(*object);
	obj->SetPos(GetPosFromID(id));
	m_Objects.push_back(obj);
}

void GridLevel::FillLevel(LevelObject* object) {
	for (int i{};i < (m_Width*m_Height);++i)
		AddBlock(object,i);
}

void  GridLevel::Update(const float elapsedTime) {
	for (auto object : m_Objects) {
		object->Update(elapsedTime);
	}

	for (auto object : m_FreeBlocks) {
		object.first->Update(elapsedTime);
	}

}

void GridLevel::Draw() {
	for (auto object : m_Objects) {
		object->Draw();
	}

	for (auto object : m_FreeBlocks) {
		object.first->Draw();
	}
	
}

void GridLevel::Initialize() {
	for (auto object : m_Objects) {
		object->Initialize();
	}

	for (auto object : m_FreeBlocks) {
		object.first->Initialize();
	}

}

dae::Vector2 GridLevel::GetPosFromID(int ID) {
	float x = m_Position.x + (ID % m_Width)*m_BlockSize;
	float y = m_Position.y + float(ID /int(m_Height))*m_BlockSize;
	//TODO: ERROR WHEN OUTSIDE
	return { x,y };
}

void GridLevel::SetOffset(dae::Vector2 offset) {
	m_Offset = offset;
}



void GridLevel::FreeBlock(LevelObject* freedBlock, LevelObject* replacment) {
	m_FreeBlocks[freedBlock] = m_Objects[GetID(freedBlock)]->GetPos();
	m_Objects[GetID(freedBlock)] = replacment;
}

void GridLevel::LockBlock(LevelObject* lockBlock,int ID) {
	//m_FreeBlocks[lockBlock] = m_Objects[GetID(freedBlock)]->GetPos();
	//TODO: delete freeblocks lockblock inside map
	m_Objects[ID] = lockBlock;
	lockBlock->SetPos(GetPosFromID(ID));
}

void GridLevel::SetPositionFreeBlock(LevelObject* freedBlock,dae::Vector2 pos) {
	m_FreeBlocks[freedBlock] = pos;
	freedBlock->SetPos(pos);
}

dae::Vector2 GridLevel::GetPositionFreeBlock(LevelObject* freedBlock) {
	return m_FreeBlocks[freedBlock];
}



dae::Vector2 GridLevel::GetClosestPosOnLine(const dae::Vector2 &currentPos) {


	float m_deadZoneSmall = 0.05f;
	float m_deadZoneBig = 0.4f;

	float y = currentPos.y - m_Position.y;//above the level if < 0
	float x = currentPos.x - m_Position.x;//left of the level if < 0

	if (y < 0 && x < 0)
		return { m_Position.y,m_Position.x };
	if (y < 0)
		return { m_Position.y,currentPos.x };
	if (x < 0)
		return { currentPos.y,m_Position.x };


	float fy = (y / m_BlockSize);
	float fx = (x / m_BlockSize);

	float dy = fy - floor(fy);
	float dx = fx - floor(fx);

	//dae::Vector2 finalPos = GetPosFromID(int(fy)*m_Width + int(fx));
	//dae::Vector2 finalPos = GetClosestPosOnLineInSquare(currentPos, int(fy)*m_Width + int(fx));
	dae::Vector2 finalPos = GetClosestPointViaPos(currentPos);

	if (dy == 0 || dx == 0)
		return currentPos;
	

	float DistanceY = ClosestDistanceToRoundValue(dy);
	float DistanceX = ClosestDistanceToRoundValue(dx);

	if (DistanceY < DistanceX)
		if(DistanceY < m_deadZoneSmall)
			if(DistanceX < m_deadZoneBig)
				return { finalPos.x,currentPos.y };

	if (DistanceY > DistanceX)
		if (DistanceX < m_deadZoneSmall)
			if (DistanceY < m_deadZoneBig)
				return { currentPos.x,finalPos.y };
			

	if (DistanceY < DistanceX)//if y is closer
		return { currentPos.x,finalPos.y };
	else // x is closer
		return { finalPos.x,currentPos.y };


}

float GridLevel::ClosestDistanceToRoundValue(float value) {

	if (value < 0.5f) {
		return value;
	}
	else {
		return 1 - value;
	}

}

int GridLevel::GetWidth() {
	return m_Width;
}
int GridLevel::GetHeight() {
	return m_Height;
}

bool GridLevel::InsideBounds(int ID) {
	if (ID < 0 || ID >= m_Objects.size())
		return false;
	return true;
}

LevelObject* GridLevel::GetObjectWithID(int ID, Dir dir) {

	//if(ID < 0 && ID > m_)

	int x = ID % m_Width;
	//int y = ID / m_Width;

	switch (dir) {
	case Center:
			return m_Objects[ID];
		break;
	case Left:
		if (x != 0 && InsideBounds(ID - 1))
			return m_Objects[ID - 1];
		//else //TODO: Execption or something
		break;
	case Right:
		if (x != m_Width && InsideBounds(ID + 1))
			return m_Objects[ID + 1];
		//else //TODO: Execption or something
		break;
	case Up:
		if (InsideBounds(ID - m_Width))
			return m_Objects[ID - m_Width];
		//else //TODO: Execption or something
		break;
	case Down:
		if (InsideBounds(ID + m_Width))
			return m_Objects[ID + m_Width];
		//else //TODO: Execption or something
		break;
	}
	return nullptr;
}

float GridLevel::GetBlockSize() {
	return m_BlockSize;
}

LevelObject* GridLevel::GetObjectWithPos(dae::Vector2 pos) {
	
	return m_Objects[GetClosestIDViaPos(pos)];
}

int GridLevel::GetID(const LevelObject* object) const{
	for (int i{}; i < m_Objects.size(); ++i) {
		if (m_Objects[i] == object)
			return i;
	}
	return -1;
}

dae::Vector2 GridLevel::GetClosestPointViaPos(dae::Vector2 pos) {
	float smallest = m_BlockSize*2;
	dae::Vector2 point{0,0};
	float temp{0};
	for (auto obj : m_Objects) {
		temp = obj->GetPos().DistanceTo(pos);
		if (smallest > temp) {
			smallest = temp;
			point = obj->GetPos();
		}
	}
	return point;
}
//TODO: MAybe one function instead of 2

//TODO: Make this pos/width to ID and not over all objects
int GridLevel::GetClosestIDViaPos(dae::Vector2 pos) const {
	float smallest = m_BlockSize * 2;
	int ID = -1;
	float temp{ 0 };
	for (int i{};i< m_Objects.size(); ++i) {
		
		temp = m_Objects[i]->GetPos().DistanceTo(pos);
		if (smallest > temp) {
			smallest = temp;
			ID = i;
		}
	}
	return ID;
}

//TODO: is beter than GetClosestPointViaPos but need to test first
dae::Vector2 GridLevel::GetClosestPosOnLineInSquare(dae::Vector2 pos,int ID) {
	
	dae::Vector2 FirstIDPos = GetPosFromID(ID);
	float smallest = FirstIDPos.DistanceTo(pos);
	int finalID = ID;

	float temp = GetPosFromID(ID + 1).DistanceTo(pos);
	if (temp < smallest) {
		smallest = temp;
		finalID = ID + 1;
	}

	temp = GetPosFromID(ID -1).DistanceTo(pos);
	if (temp < smallest) {
		smallest = temp;
		finalID = ID - 1;
	}

	temp = GetPosFromID(ID - m_Width).DistanceTo(pos);
	if (temp < smallest) {
		smallest = temp;
		finalID = ID - m_Width;
	}

	temp = GetPosFromID(ID + m_Width).DistanceTo(pos);
	if (temp < smallest) {
		smallest = temp;
		finalID = ID + m_Width;
	}

	return GetPosFromID(finalID);
}

//TODO: Enum for circle round
//TODO: get next id in line etc....

