#include "DxLib.h"
#include "Player/Player.h"
#include "Input/Input.h"

int main()
{
	// DxLib‚Ì‰Šú‰»
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	Player player;
	Input input;
	while (true) {
		input.Update();
		if (input.IsKeyDown(KEY_INPUT_ESCAPE)) break;
		player.Update(input);
		ClearDrawScreen();
		player.Draw(0); // ƒJƒƒ‰ˆÊ’u‚Í0‚ÅŒÅ’è
		ScreenFlip();
		input.LateUpdate();
	}
	DxLib_End();
	return 0;
}