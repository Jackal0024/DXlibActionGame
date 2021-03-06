#include "Capsule.h"
#include"DxLib.h"

Capsule::Capsule(const Line& line, const float radius):
	mLine(line),
	mRadius(radius),
	isAlive(true)
{
}

Capsule::Capsule(const Vector3 length,const float radius):
	mLine(Line({ 0,0,0 }, length)),
	mRadius(radius),
	isAlive(true)
{
}

Capsule::~Capsule()
{
}

bool Capsule::Intersects(const Capsule & other) const
{
	return CollisionCapsuleAndCapsule(other);
}

Capsule Capsule::Move(const Vector3 & position) const
{
	auto v = mLine.mEndPos - mLine.mStartPos;
	return Capsule(Line(position,position + v),mRadius);
}

Capsule Capsule::Translate(const Vector3 & position) const
{
	return Capsule(Line(mLine.mStartPos + position,mLine.mEndPos + position),mRadius);
}

Capsule Capsule::Transform(const Matrix & matrix) const
{
	return Capsule(Line(Vector3::Transform(mLine.mStartPos, matrix), Vector3::Transform(mLine.mEndPos, matrix)), mRadius * matrix.Scale().y);
}

void Capsule::Draw() const
{
	DrawCapsule3D(mLine.mStartPos, mLine.mEndPos, mRadius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

bool Capsule::CollisionCapsuleAndCapsule(const Capsule & other) const
{
	return HitCheck_Capsule_Capsule(mLine.mStartPos, mLine.mEndPos,mRadius,other.mLine.mStartPos, other.mLine.mEndPos, other.mRadius) != 0;;
}
