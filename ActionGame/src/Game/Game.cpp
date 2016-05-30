#include<string>
#include "Game.h"
#include"DxLib.h"
#include"../Input/Input.h"
#include"../Input/KeyNum.h"
#include"../Math/Vector3.h"
#include"../Math//Matrix.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::initialize()
{
}

void Game::Update()
{
	
}

void Game::Draw()
{
	/*MATRIX m1 = MGetIdent();
	MATRIX m2 = Matrix(10,10,10,10,
						10,10,10,10,
						10,10,10,10,
						10,10,10,10
						);
	m1 += m2;
	for (int i = 0; i < 4; i++)
	{
		DrawFormatString(0,20 * i, GetColor(255, 255, 255), "MTRIX[%d]  %f %f %f %f",i,m1.m[i][0], m1.m[i][1], m1.m[i][2], m1.m[i][3]);
	}*/

	Vector3 v1(0, 0.1, 0);
	Vector3 v2(0, 0.9f, 0.3f);
	v1 = VCross(v1, v2);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Vector  x=%f y=%f z=%f ", v1.x, v1.y, v1.z);
	
	
}

void Game::Finish()
{
}
