#pragma once
class CollisionManager : public Observer
{
public:
	CollisionManager();
	~CollisionManager();

	void Update();
	void AddCollision(CollisionObject* object);
	void Remove(CollisionObject* object);
	void RemoveAll();
	void ResetSceneCol(int IDs);

	void onNotify( Event event) override;

private:
	std::vector<CollisionObject*> m_Objects;
	std::vector<std::pair<int,std::vector<CollisionObject*>>> m_OtherObjects;

	void SwitchScenes(bool avtivate);

};

