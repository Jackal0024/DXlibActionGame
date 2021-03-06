/*
*ナンバーテクスチャ
*概要：数字テクスチャを分割して描画するクラス
*/
#pragma once
#include"../../Math/Vector3.h"
#include"DxLib.h"

#include<string>

class NumberTexture
{
public:
	NumberTexture();
	NumberTexture(std::string fileName,int all
		,int xnum, int ynum
		,int xSize, int ySize);
	~NumberTexture();
	void Draw(Vector3 pos,int value) const;
	void Draw(Vector3 pos, std::string value) const;

private:
	int mNumHandle[10];
	int mXSize, mYSize;

};
