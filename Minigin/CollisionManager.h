#pragma once
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update();
	void AddCollision(CollisionObject* object);
	void Remove(CollisionObject* object);

private:
	std::vector<CollisionObject*> m_Objects;
};

