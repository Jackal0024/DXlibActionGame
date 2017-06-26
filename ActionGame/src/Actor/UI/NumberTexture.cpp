#include "NumberTexture.h"

NumberTexture::NumberTexture(){}

NumberTexture::NumberTexture(std::string fileName, int all
	, int xnum, int ynum
	, int xSize, int ySize) :
	mXSize(xSize),
	mYSize(ySize)
{
	LoadDivGraph(fileName.c_str(), all, xnum, ynum,
		mXSize, mYSize, mNumHandle);
}

NumberTexture::~NumberTexture()
{
	//for (int i = 0; i < 10; i++)
	//{
	//	DeleteGraph(mNumHandle[i]);
	//}
}

void NumberTexture::Draw(Vector3 pos, int value) const
{
	Draw(pos, std::to_string(value));
}

void NumberTexture::Draw(Vector3 pos, std::string value) const
{
	for (int i = 0; i < (int)value.size(); ++i) {
		if (value[i] == ' ') continue;
		const int n = value[i] - '0';
		DrawGraph((int)(pos.x + (mXSize * i)),(int)pos.y,mNumHandle[n],TRUE);
	}
}
