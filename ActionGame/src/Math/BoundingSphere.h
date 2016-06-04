#pragma once

#include"Vector3.h"
#include"Matrix.h"

class BoundingSphere
{
public:
	BoundingSphere(const Vector3& center, float radius);
	BoundingSphere(float radius = 0.0f);
	BoundingSphere Translate(const Vector3& position) const;
	BoundingSphere Transform(const Matrix& matrix)const;
	bool Intersects(const BoundingSphere& other) const;
	void Draw() const;

private:
	bool CollisionSphereAndSphere(Vector3 v1, float r1, Vector3 v2, float r2) const;

private:
	Vector3 mCenter;
	float mRadius;

};