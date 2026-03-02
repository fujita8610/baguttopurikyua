#include "DxLib.h"

//scene関連
#include "scene/sceneManager.h"
#include "scene/title/titleScene.h"

//ゲームデバッグ
#include "../Source/GameDebug/GameDebug.h"


int main()
{
    // DxLib初期化
    if (DxLib_Init() == -1) return -1;

    SetDrawScreen(DX_SCREEN_BACK);

    // 最初のシーン
    SceneManager::ChangeScene(new TitleScene());

    // メインループ
    while (ProcessMessage() == 0)
    {
        // 更新
        SceneManager::Update();

        // 描画
        ClearDrawScreen();

        SceneManager::Draw();

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}