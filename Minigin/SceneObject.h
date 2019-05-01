#pragma once
//#include "Scene.h"

namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update(const float elapsedTime) = 0;
		virtual void Render() const = 0;
		virtual void Initialize() = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

	};
}
