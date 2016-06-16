#include "Field.h"

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

void Field::Draw() const
{
	//MV1SetPosition(mModelHandle,VGet(0.0f,-1.0f,0.0f));
	MV1DrawModel(mModelHandle);
}
