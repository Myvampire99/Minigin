#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

dae::Transform::Transform()
	:mPosition{0,0,0}
{}


dae::Vector3 dae::Transform::GetPosition() const 
{ return mPosition; }