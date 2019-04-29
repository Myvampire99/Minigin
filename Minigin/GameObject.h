#pragma once
#include "SceneObject.h"
#include "Transform.h"

class BaseComponent;

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		void Update(const float elapsedTime) override;
		void Render() const override;
		void Initialize() override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		dae::Vector2 GetPos() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		
		void AddComponent(BaseComponent *cmp);

	private:
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;

		std::vector<BaseComponent*> m_pComponents;
		//TODO: + Children 





	public:
		template <class T>
		T* GetComponent()//search in children ?
		{
			const type_info& ti = typeid(T);
			for (auto* comp : m_pComponents) {
				if (typeid(*comp) == ti) { // does it really need to check for nullptr ??
					return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}
		
	};
}
