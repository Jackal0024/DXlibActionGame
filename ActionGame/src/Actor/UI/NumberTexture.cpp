#include "NumberTexture.h"

NumberTexture::NumberTexture(std::string fileName, int all
	, int xnum, int ynum
	, int xSize, int ySize) :
	mXSize(xSize),
	mYSize(ySize)
{
	LoadDivGraph(fileName.c_str(), all, xnum, ynum,
		mXSize, mYSize, mNumHandle);
}

void NumberTexture::Draw(Vector3 pos, int value)
{
	Draw(pos, std::to_string(value));
}

void NumberTexture::Draw(Vector3 pos, std::string value)
{
	for (int i = 0; i < (int)value.size(); ++i) {
		if (value[i] == ' ') continue;
		const int n = value[i] - '0';
		DrawGraph(pos.x + (mXSize * i),pos.y,mNumHandle[n],TRUE);
	}
}
