#pragma once
#include"Line.h"

class Capsule
{
public:
	Capsule(const Line& line, const float radius);
	~Capsule();
	bool Intersects(const Capsule& other) const;
	void Draw() const;

private:
	Line mLine;
	float mRadius;
	
public:
	bool CollisionCapsuleAndCapsule(const Capsule & other) const;

};
