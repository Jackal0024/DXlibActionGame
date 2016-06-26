#include "Capsule.h"
#include"DxLib.h"

Capsule::Capsule(const Line& line, const float radius):
	mLine(line),
	mRadius(radius)
{
}

Capsule::Capsule(const Vector3 length,const float radius):
	mLine(Line({ 0,0,0 }, length)),
	mRadius(radius)
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
	return Capsule(Line(matrix.Transform(mLine.mStartPos), matrix.Transform(mLine.mEndPos))
		,mRadius * matrix.GetScale().y);
}

void Capsule::Draw() const
{
	DrawCapsule3D(mLine.mStartPos, mLine.mEndPos, mRadius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

bool Capsule::CollisionCapsuleAndCapsule(const Capsule & other) const
{
	return HitCheck_Capsule_Capsule(mLine.mStartPos, mLine.mEndPos, mRadius
		, other.mLine.mStartPos, other.mLine.mEndPos, other.mRadius);
	//Vector3 p1, p2;
	//float t1, t2;
	//float d = Line::LineLineDistance(mLine, other.mLine, p1, p2, t1, t2);
	//return (d <= mRadius + other.mRadius);
}
