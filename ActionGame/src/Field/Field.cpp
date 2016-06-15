#include "Field.h"

Field::Field(int modelhandle)
{
	mModelHandle = modelhandle;
}

bool Field::Collision() const
{
	return false;
}

void Field::Draw() const
{
	MV1SetPosition(mModelHandle,VGet(0.0f,-1.0f,0.0f));
	MV1DrawModel(mModelHandle);
}
