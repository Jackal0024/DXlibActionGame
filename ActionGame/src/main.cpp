#include "DxLib.h"
#include"Game\Game.h"
#include"System\ConstantList\WindowSize.h"
#include"Effect\Base\EffekseerDxLib.h"

#pragma comment(linker, "/entry:mainCRTStartup")

int main() {

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

	//DXライブラリの初期化
	DxLib_Init();

	//エフェクシールの初期化
	Effkseer_Init(2048, 2048, 32);

	//バックグラウンドカラー
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();


	//更新処理
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		UpdateEffekseer(60 * deltatime);;

		Effekseer_Sync3DSetting();

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		game.Draw();
		DrawEffekseer();

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
	Effkseer_End();
	DxLib_End();
	return 0;
}