#pragma once
class VelocityComponent : public BaseComponent
{
public:
	VelocityComponent();
	VelocityComponent(dae::Vector2 vel);
	~VelocityComponent();

	void Update(float elapsedTime) override;
	void Draw() override;
	void Initialize() override;

	void SetVelocity();
	dae::Vector2 GetVelocity();

private:
	dae::Vector2 m_Velocity;
	CollisionComponent *m_CollisionComponent;
	bool m_DeleteSelf = false;
};

