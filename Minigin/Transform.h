#pragma once
//#pragma warning(push)
//#pragma warning (disable:4201)
//#include <glm/vec3.hpp>
//#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		
		Vector3 mPosition;
		float mAngle;

	public:
		Transform();

		Vector2 GetPosition2D() const { return { mPosition.x,mPosition.y }; }
		Vector3 GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(float x, float y);
		void SetPosition(const dae::Vector2 &pos);
		void Translate(const dae::Vector2 &forward);//TODO: Z?
		void SetAngle(float angle);
		float GetAngle() const;
	};
}
