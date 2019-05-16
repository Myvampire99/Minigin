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
	, mAngle{0}
{}


dae::Vector3 dae::Transform::GetPosition() const 
{ return mPosition; }

void dae::Transform::Translate(const dae::Vector2 &forward) {

	auto forvec = forward;
	float angleRAD = mAngle * 3.1415f / 180.f;
	forvec.x = cos(angleRAD)*forward.x - sin(angleRAD)*forward.y;
	forvec.y = sin(angleRAD)*forward.x + cos(angleRAD)*forward.y;

	mPosition.x += forvec.x;
	mPosition.y += forvec.y;
}

void dae::Transform::SetAngle(float angle) {
	mAngle = angle;
}

float dae::Transform::GetAngle() const{
	return mAngle;
}

void dae::Transform::SetPosition(float x, float y) {
	SetPosition(x, y, mPosition.z);
}

void dae::Transform::SetPosition(const dae::Vector2 &pos) {
	SetPosition(pos.x, pos.y, mPosition.z);
}