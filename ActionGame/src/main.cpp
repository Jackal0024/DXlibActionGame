#include "DxLib.h"
#include"Game\Game.h"
#include"System\ConstantList\WindowSize.h"
#include"EffekseerForDXLib.h"

#if _DEBUG
int main() 
{
	//ゲーム本体を宣言
	Game game;
	//ウィンドウモード TRUEならウィンドウモード
	bool isWindow = TRUE;
	//デルタタイム
	float deltatime = 0;
	//経過時間
	float timer = 0;

	//ログを出ないように
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(isWindow);
	//解像度の設定
	SetGraphMode(WIDTH, HEIGHT, 16);
	//スクリーンモードに変えてもエフェクトが消えないように
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//ピクセルライティングをするか？
	SetUsePixelLighting(TRUE);
	//Direct3Dのバージョン指定
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//DXライブラリの初期化
	DxLib_Init();

	//エフェクシールの初期化
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//バックグラウンドカラー
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//更新処理
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Effekseer_Sync3DSetting();
		int Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		UpdateEffekseer3D();;

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		game.Draw();
		DrawEffekseer3D();

		//デバッグ表示　デルタタイムと経過時間
		//DrawFormatString(0, HEIGHT-80, GetColor(255, 255, 255), "Timer = %f", timer);
		//DrawFormatString(0, HEIGHT-40, GetColor(255, 255, 255), "DeltaTimer = %f", deltatime);

		//デバッグ表示　XYZ表示
		/*DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));*/

		ScreenFlip();
		deltatime =  (float)(GetNowCount() - Time);
		deltatime /= 1000; //1秒=1000m/s
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}

#endif

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//ゲーム本体を宣言
	Game game;
	//ウィンドウモード TRUEならウィンドウモード
	bool isWindow = TRUE;
	//デルタタイム
	float deltatime = 0;
	//経過時間
	float timer = 0;

	//ログを出ないように
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(isWindow);
	//解像度の設定
	SetGraphMode(WIDTH, HEIGHT, 16);
	//スクリーンモードに変えてもエフェクトが消えないように
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//ピクセルライティングをするか？
	SetUsePixelLighting(TRUE);
	//Direct3Dのバージョン指定
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//DXライブラリの初期化
	DxLib_Init();

	//エフェクシールの初期化
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//バックグラウンドカラー
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//更新処理
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		Effekseer_Sync3DSetting();
		auto Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		UpdateEffekseer3D();;

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		game.Draw();
		DrawEffekseer3D();

		//デバッグ表示　デルタタイムと経過時間
		//DrawFormatString(0, HEIGHT-80, GetColor(255, 255, 255), "Timer = %f", timer);
		//DrawFormatString(0, HEIGHT-40, GetColor(255, 255, 255), "DeltaTimer = %f", deltatime);

		//デバッグ表示　XYZ表示
		/*DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));*/

		ScreenFlip();
		deltatime = (float)(GetNowCount() - Time);
		deltatime /= 1000; //1秒=1000m/s
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}