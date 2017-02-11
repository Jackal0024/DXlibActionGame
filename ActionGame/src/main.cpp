#include "DxLib.h"
#include"Game\Game.h"
#include"System\ConstantList\WindowSize.h"
#include"EffekseerForDXLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game;
	float deltatime = 0;
	//�o�ߎ���
	float timer = 0;

	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WIDTH, HEIGHT, 16);
	ChangeWindowMode(FALSE);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetUsePixelLighting(TRUE);
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	DxLib_Init();

	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

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

		//DrawFormatString(0, HEIGHT-80, GetColor(255, 255, 255), "Timer = %f", timer);
		//DrawFormatString(0, HEIGHT-40, GetColor(255, 255, 255), "DeltaTimer = %f", deltatime);

		/*DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));*/

		ScreenFlip();
		deltatime = GetNowCount() - Time;
		deltatime /= 1000; //1�b=1000m/s
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}