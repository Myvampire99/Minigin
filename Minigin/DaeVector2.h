#pragma once

namespace dae {
	struct Vector2
	{
		Vector2() :x{}, y{}{}
		Vector2(float x, float y) :x{ x }, y{ y }{}

		float DistanceTo(Vector2 pos) {
			float X{ pos.x - x };
			float Y{ pos.y - y };
			return float(sqrt(X*X + Y * Y));
		}

		bool operator==(const Vector2& lhs)
		{
			if (lhs.x == this->x && lhs.y == this->y)
				return true;
			return false;
		}


		float x, y;
	};
}

namespace dae {
	struct Vector3
	{
		Vector3() :x{}, y{}, z{}{}
		Vector3(float x, float y, float z) :x{ x }, y{ y }, z{ z }{}
		float x, y, z;
	};
}