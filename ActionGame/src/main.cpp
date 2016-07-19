#include "DxLib.h"
#include"Game\Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game;
	float deltatime = 0;
	//Œo‰ßŽžŠÔ
	float timer = 0;
	SetUseZBuffer3D(TRUE);
	ChangeWindowMode(TRUE);
	//SetWindowSizeExtendRate(1.3f);

	SetBackgroundColor(0, 0, 255);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		auto Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);
		game.Draw();

		DrawFormatString(0, 440, GetColor(255, 255, 255), "Timer =%f", timer);
		DrawFormatString(0, 460, GetColor(255, 255, 255), "DeltaTimer =%f", deltatime);
		DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));

		ScreenFlip();
		deltatime = GetNowCount() - Time;
		deltatime /= 1000;
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}