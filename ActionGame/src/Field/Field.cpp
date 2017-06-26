#include "Field.h"
#include<math.h>
#include"../Math/MathHelper.h"

Field::Field(int modelhandle)
{
	mModelHandle = modelhandle;

	MV1SetupCollInfo(mModelHandle, -1);
}

Field::~Field()
{
	MV1DeleteModel(mModelHandle);
}

bool Field::Collision(const Vector3& start, const Vector3& end, Vector3& out_heigt) const
{	
	auto HitPoly = MV1CollCheck_Line(mModelHandle, -1, start, end);
	if (HitPoly.HitFlag == 1)
	{
		out_heigt = (Vector3)HitPoly.HitPosition;
		return true;
	}
	else
	{
		return false;
	}
}

bool Field::Collision(Vector3 & start, const Vector3 & end, const float & r)
{
	auto HitPoly = MV1CollCheck_Capsule(mModelHandle, -1, start, end, r);
	if (HitPoly.HitNum >= 1)
	{
		for (int i = 0; i < HitPoly.HitNum; i++)
		{
			float angel = Vector3::Angle(Vector3::Normalize(HitPoly.Dim[i].Normal), Vector3(0, 1, 0));
			if (fabsf(angel) >= 90)
			{
				start =start +  (Vector3)HitPoly.Dim[i].Normal * r;
				MV1CollResultPolyDimTerminate(HitPoly);
				return true;
			}
		}
	}
	MV1CollResultPolyDimTerminate(HitPoly);
	return false;
}

bool Field::Collision(Vector3 & start, const Vector3 & end, const float & r, Vector3 & velocity)
{
	auto HitPoly = MV1CollCheck_Capsule(mModelHandle, -1, start, end, r);
	if (HitPoly.HitNum >= 1 || Collision(start, velocity, r))
	{
		for (int i = 0; i < HitPoly.HitNum; i++)
		{
			float angel = Vector3::Angle(Vector3::Normalize(HitPoly.Dim[i].Normal), Vector3(0, 1, 0));
			if (fabsf(angel) >= 60)
			{
				start = start + (Vector3)HitPoly.Dim[i].Normal * r;
				velocity = velocity + (Vector3)(-VDot(velocity, HitPoly.Dim[i].Normal) * HitPoly.Dim[i].Normal);
				MV1CollResultPolyDimTerminate(HitPoly);
				return true;
			}
		}
	}
	MV1CollResultPolyDimTerminate(HitPoly);
	return false;
}

void Field::Draw() const
{

	MV1DrawModel(mModelHandle);
}
