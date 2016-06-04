#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(const Vector3 & center, float radius):
	mCenter(center),mRadius(radius)
{
}

BoundingSphere::BoundingSphere(float radius):
	BoundingSphere(Vector3(0.0f,0.0f,0.0f),radius)
{
}

BoundingSphere BoundingSphere::Translate(const Vector3 & position) const
{
	return BoundingSphere(mCenter+position,mRadius);
}

BoundingSphere BoundingSphere::Transform(const Matrix & matrix) const
{
	return BoundingSphere(matrix.Transform(mCenter),mRadius*matrix.GetScale().y);
}

bool BoundingSphere::Intersects(const BoundingSphere & other) const
{
	return CollisionSphereAndSphere(mCenter, mRadius, other.mCenter, other.mRadius);
}

void BoundingSphere::Draw() const
{
	DrawSphere3D(mCenter, mRadius, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

bool BoundingSphere::CollisionSphereAndSphere(Vector3 v1, float r1, Vector3 v2, float r2) const
{
	//(x2 - x1) ^ 2 + (y2 - y1) ^ 2 + (z2 - z1) ^ 2 <= (r1 + r2) ^ 2
	return VSize((v2 - v1)) <= (r1 + r2);
	return ((v2.x - v1.x) * 2) + ((v2.y - v1.y) * 2) + ((v2.z - v1.z) * 2) <= (r1 + r2) * 2;
}
