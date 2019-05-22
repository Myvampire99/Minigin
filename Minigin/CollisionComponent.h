#pragma once
class CollisionComponent : public BaseComponent
{
public:
	CollisionComponent();
	~CollisionComponent();

	void AddCollision(CollisionObject* object);
	const std::vector<CollisionObject*>& GetCollisions();
	void Remove(CollisionObject* object);

	void Update(const float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

private:
	std::vector<CollisionObject*> m_Collisions;
};

