/*
*ファイアーウォール
*概要：ファイアーパーツを同時に出す魔法
*/
#pragma once
#include"../../Base/Actor.h"

class FireWall : public Actor
{
public:
	FireWall(IWorld* world, Vector3 position, const Vector3& Velocity, Tag tag,float power);
	~FireWall();
};
