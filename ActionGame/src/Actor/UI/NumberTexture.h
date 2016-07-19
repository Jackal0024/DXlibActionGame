#pragma once
#include"../../Math/Vector3.h"
#include"DxLib.h"

#include<string>

class NumberTexture
{
public:
	NumberTexture(std::string fileName,int all
		,int xnum, int ynum
		,int xSize, int ySize);
	void Draw(Vector3 pos,int value);
	void Draw(Vector3 pos, std::string value);

private:
	int mNumHandle[10];
	int mXSize, mYSize;

};
