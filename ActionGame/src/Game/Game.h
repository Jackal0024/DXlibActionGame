/*
*ゲームクラス
*概要：全体の更新や描画を管理するクラス
*/
#ifndef GAME_H_
#define GAME_H_

#include"../World/World.h"
#include"../Scene/Base/SceneManager.h"
//ゲーム本体
class Game
{
public:
	Game();
	~Game();
	//初期化処理
	void initialize();
	//更新
	void Update(float deltatime);
	//描画
	void Draw();
	//終了処理
	void Finish();

private:
	//シーンマネージャー
	SceneManager mSceneManager;

};

#endif