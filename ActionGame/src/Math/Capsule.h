#ifndef CAPSULE_H_
#define CAPSULE_H_

#include"Line.h"
#include"Matrix.h"

class Capsule
{
public:
	Capsule(const Line& line, const float radius);
	Capsule(const Vector3 length,const float radius);
	~Capsule();
	bool Intersects(const Capsule& other) const;
	Capsule Move(const Vector3& position) const;
	Capsule Translate(const Vector3& position) const;
	Capsule Transform(const Matrix& matrix)const;
	void Draw() const;

public:
	Line mLine;
	float mRadius;
	bool isAlive;
	
public:
	bool CollisionCapsuleAndCapsule(const Capsule & other) const;

};

#endif
