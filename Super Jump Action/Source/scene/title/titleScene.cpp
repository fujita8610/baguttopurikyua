#include "DxLib.h"

//scene関連
#include "titleScene.h"
#include "../sceneManager.h"
#include "../../scene/gameScene/gameScene.h"

void TitleScene::Init()
{
    //カーソル
    cursor = 0;

   // 画像読み込み
   // titleFrameHandle = LoadGraph("Data/UI/title_frame.png");
    selectBarHandle = LoadGraph("Data/Title/selectBar1.png");
}

void TitleScene::Update()
{
    input.Update();

    // ↓キー
    if (input.IsKeyDownTrigger(KEY_INPUT_DOWN))
    {
        cursor++;
        if (cursor >= MENU_MAX)
            cursor = 0;
    }

    // ↑キー
    if (input.IsKeyDownTrigger(KEY_INPUT_UP))
    {
        cursor--;
        if (cursor < 0)
            cursor = MENU_MAX - 1;
    }

    // 決定
    if (input.IsKeyDownTrigger(KEY_INPUT_RETURN))
    {
        switch (cursor)
        {
        case 0: // ゲームスタート
            SceneManager::ChangeScene(new GameScene());
            return;

        case 1: // 続きから
            // 今は未実装
            break;

        case 2: // オプション
            // 今後実装
            break;

        case 3: // ゲーム終了
            DxLib_End();
            break;
        }
    }

    input.LateUpdate();
}

void TitleScene::Draw()
{
    DrawString(200, 150, "SUPER JUMP ACTION", GetColor(255, 255, 255));

    const char* menu[MENU_MAX] =
    {
        "GAME START",
        "CONTINUE",
        "OPTION",
        "EXIT"
    };

    int baseX = 200;
    int baseY = 250;

    for (int i = 0; i < MENU_MAX; i++)
    {
        int y = baseY + i * 50;

        if (i == cursor)
        {
            // 選択バー画像
            DrawGraph(baseX - 40, y - 10, selectBarHandle, TRUE);
            DrawString(baseX, y, menu[i], GetColor(255, 255, 0));
        }
        else
        {
            DrawString(baseX, y, menu[i], GetColor(255, 255, 255));
        }

        // ===== デバッグ枠 =====
        if (GameDebug::IsDebug())
        {
            DrawBox(baseX - 40, y - 10,
                baseX + 300, y + 30,
                GetColor(255, 0, 0), FALSE);
        }
    }
}

void TitleScene::End()
{

}