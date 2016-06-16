#include "DxLib.h"
#include"Game\Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game game;
	SetUseZBufferFlag(TRUE);
	
	ChangeWindowMode(TRUE);
	SetBackgroundColor(0, 0, 255);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawZBuffer(DX_SCREEN_BACK);
	game.initialize();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		game.Update();
		game.Draw();
	}
	game.Finish();
	DxLib_End();
	return 0;
}