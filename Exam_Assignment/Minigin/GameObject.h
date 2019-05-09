#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		void Update(const float elapsedTime) override;
		void Render() const override;
		void Initialize() override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//template?
		void AddComponent(BaseComponent *cmp);

	private:
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;

		std::vector<BaseComponent*> m_pComponents;
		//TODO: + Children 



	};
}