#pragma once

class BaseComponent
{
public:
	BaseComponent(); // = default
	virtual ~BaseComponent();
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	std::shared_ptr<dae::GameObject> m_GameObject;
	virtual void Update(float elapsedTime) = 0;
	virtual void Draw() = 0;
	virtual void Initialize() = 0;
};

