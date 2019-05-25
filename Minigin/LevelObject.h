#pragma once
class CollisionObject;
class LevelObject
{
public:
	LevelObject(std::string path);
	virtual ~LevelObject() = default;

	virtual void Update(float elapsedTime);
	void Draw();
	virtual void Initialize();

	void SetPos(dae::Vector2 pos);
	void SetSize(float size);
	dae::Vector2 GetPos();

	bool IsWalkable();
	void SetWalkable(bool iswalkable);

	CollisionObject* GetCollision();
protected:
	CollisionObject* m_Collision;
private:
	std::shared_ptr<dae::Texture2D> m_Texture;
	dae::Vector2 m_Pos;
	float m_Size;
	bool m_IsWalkable;
};

