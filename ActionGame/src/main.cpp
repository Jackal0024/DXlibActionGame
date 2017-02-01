#include "DxLib.h"
#include"Game\Game.h"
#include"System\ConstantList\WindowSize.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game;
	float deltatime = 0;
	//Œo‰ßŽžŠÔ
	float timer = 0;

	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WIDTH, HEIGHT, 16);
	ChangeWindowMode(TRUE);
	SetUsePixelLighting(TRUE);

	DxLib_Init();
	SetBackgroundColor(0, 0, 255);

	SetDrawScreen(DX_SCREEN_BACK);
	game.initialize();

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		auto Time = GetNowCount();
		timer += deltatime;

		game.Update(deltatime);

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		game.Draw();

		//DrawFormatString(0, HEIGHT-80, GetColor(255, 255, 255), "Timer = %f", timer);
		//DrawFormatString(0, HEIGHT-40, GetColor(255, 255, 255), "DeltaTimer = %f", deltatime);

		/*DrawLine3D(Vector3(0, 0, 0), Vector3(100, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 100, 0), GetColor(0, 255, 0));
		DrawLine3D(Vector3(0, 0, 0), Vector3(0, 0, 100), GetColor(0, 0, 255));*/

		ScreenFlip();
		deltatime = GetNowCount() - Time;
		deltatime /= 1000; //1•b=1000m/s
		deltatime = min(deltatime, 0.1f);
	}
	game.Finish();
	DxLib_End();
	return 0;
}