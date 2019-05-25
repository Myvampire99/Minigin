#include "MiniginPCH.h"
#include "LevelObject.h"
#include "ResourceManager.h"

LevelObject::LevelObject(std::string path)
	: m_IsWalkable{true}
	, m_Collision{nullptr}
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}


void LevelObject::Update(float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
}

void LevelObject::Draw() {
	if (m_Texture != nullptr)
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Pos.x, m_Pos.y ,m_Size, m_Size);
	//else
		//LOG::ERROR
}

void LevelObject::Initialize() {
	
}

CollisionObject* LevelObject::GetCollision() {
	return m_Collision;
}

bool LevelObject::IsWalkable(){
	return m_IsWalkable;
}

void LevelObject::SetWalkable(bool iswalkable) {
	m_IsWalkable = iswalkable;
}

//void LevelObject::SetTexture(dae::Texture2D * texture) {
//	m_Texture = texture;
//}

void LevelObject::SetPos(dae::Vector2 pos) {
	m_Pos = pos;
}

void LevelObject::SetSize(float size) {
	m_Size = size;
}

dae::Vector2 LevelObject::GetPos() {
	return m_Pos;
}