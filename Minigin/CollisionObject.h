#pragma once
class CollisionObject
{
public:
	CollisionObject();
	~CollisionObject();

	const std::vector<dae::Vector2> &GetAllPoints();
	virtual bool CheckPointsIfInside(const std::vector<dae::Vector2> &Points) const = 0;
	void SetCurrentCollisions(const std::vector<CollisionObject*> &collisions);
	void AddCollision(CollisionObject* collisions);
	void ClearAllCollisions();
	const std::vector<CollisionObject*> &GetCurrentCollisions() const;

	void SetIsTrigger(bool istrigger);
	bool IsTrigger();

	void SetPosition(dae::Vector2);
	dae::Vector2 GetPosition();
protected:
	std::vector<dae::Vector2> m_Points;
private:
	std::vector<CollisionObject*> m_CurrentCollisions;
	bool m_IsTrigger;
};

