#pragma once
#include "SceneObject.h"

	class BaseComponent;

namespace dae
{

	class GameObject final : public SceneObject, public std::enable_shared_from_this<GameObject>
	{
	public:

		void SetEnabled(bool enabled);
		bool GetEnabled();
		void MarkForDelete(bool marked = true);
		bool GetMarkForDelete();

		
		void Update(const float elapsedTime) override;
		void Render() const override;
		void Initialize() override;


		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void SetPosition(dae::Vector2 pos);

		dae::Vector2 GetPos() const;

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		
		void AddComponent(BaseComponent *cmp);
		dae::Transform* GetTransform();

		

	private:
		dae::Transform *mTransform;
		std::shared_ptr<Texture2D> mTexture;

		std::vector<BaseComponent*> m_pComponents;
		bool m_Enabled;
		bool MarkedForDelete = false;
	public:

		template <class T>
		void RemoveComponent()
		{
			for (unsigned int i{};i< m_pComponents.size();++i){
				if (dynamic_cast<T*>(m_pComponents[i]) != nullptr) {
					delete m_pComponents[i];
					m_pComponents.erase(m_pComponents.begin()+i);
					return;
				}
			}
		}

	//	template <class T>
		//void RequestDeletionOfComponent();


		template <class T>
		T* GetComponent()
		{
			if (m_pComponents.size() == 0)
				return nullptr;

			for (auto* comp : m_pComponents) {
				if (dynamic_cast<T*>(comp) != nullptr) {
						return static_cast<T*>(comp);
				}
			}
			return nullptr;
		}
		
	};
}
