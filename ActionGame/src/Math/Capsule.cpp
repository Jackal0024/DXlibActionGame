#include "Capsule.h"

Capsule::Capsule(const Line& line, const float radius):
	mLine(line),
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
