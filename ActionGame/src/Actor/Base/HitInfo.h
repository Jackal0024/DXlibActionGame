/*
*ヒットクラス
*概要：攻撃の情報
*/
#pragma once
#include"Actor.h"

/*
*
*攻撃が当たった時の情報を格納しておく
*/

struct Hitinfo
{
	//当たった場所
	Vector3 position;
	//ダメージ量
	float damage;
};
