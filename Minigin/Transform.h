#pragma once
//#pragma warning(push)
//#pragma warning (disable:4201)
//#include <glm/vec3.hpp>
//#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		
		dae::Vector3 mPosition;

	public:
		Transform();

		dae::Vector2 GetPosition2D() const { return { mPosition.x,mPosition.y }; }
		dae::Vector3 GetPosition() const;
		void SetPosition(float x, float y, float z);
	};
}
