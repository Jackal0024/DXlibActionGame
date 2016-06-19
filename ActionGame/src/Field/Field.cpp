#include "Field.h"
#include<math.h>

Field::Field(int modelhandle)
{
	mModelHandle = modelhandle;

	MV1SetupCollInfo(mModelHandle, -1, 8, 8, 8);
}

bool Field::Collision(const Vector3& start, const Vector3& end, Vector3& out_heigt) const
{	
	auto HitPoly = MV1CollCheck_Line(mModelHandle, -1, start, end);
	if (HitPoly.HitFlag == 1)
	{
		out_heigt = HitPoly.HitPosition;
		return true;
	}
	else
	{
		return false;
	}
}

bool Field::Collision(Vector3 & start, const Vector3 & end, const float & r) const
{
	auto HitPoly = MV1CollCheck_Capsule(mModelHandle, -1, start, end,r);
	if (HitPoly.HitNum >= 1)
	{
		for (int i = 0; i < HitPoly.HitNum; i++)
		{
			float cos = VDot(VNorm(HitPoly.Dim[i].Normal), Vector3(0, 1, 0));
			float angel = acos(cos) * 180 / DX_PI;
			if (fabsf(angel) >= 90)
			{
				start += HitPoly.Dim[i].Normal * r;
				return true;
			}
		}
	}
	return false;
}

void Field::Draw() const
{
	//MV1SetPosition(mModelHandle,VGet(0.0f,-1.0f,0.0f));
	MV1DrawModel(mModelHandle);
}
