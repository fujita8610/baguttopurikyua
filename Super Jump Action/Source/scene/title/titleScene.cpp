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
   // セレクトバーの読み込み
   // titleFrameHandle = LoadGraph("Data/UI/title_frame.png");
    selectBarHandle = LoadGraph("Data/Title/selectBar1.png");

    // プレイヤーRUNアニメ読み込み
    if (playerRun.Load("Data/Player/Sprites/RUN.png", 8, 1, 96, 96))
    {
        playerFrames = playerRun.GetTotal();
        playerAnim.Start(0, playerFrames - 1, 4, true);
    }

    // プレイヤー待機アニメ
    if (playerIdle.Load("Data/Player/Sprites/IDLE.png", 10, 1, 96, 96))
    {
        idleFrames = playerIdle.GetTotal();
        playerIdleAnim.Start(0, idleFrames - 1, 8, true);
    }
}

void TitleScene::Update()
{
    input.Update();

    blinkTimer++;   // 点滅用タイマー

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

    //他cppからの宣言
    playerAnim.Update();
    playerIdleAnim.Update();


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

    int baseX = 400;
    int baseY = 280;



    // 点滅用カラー
    float t = sin(blinkTimer * 0.1f);
    int brightness = 120 + (int)(t * 60);
    int blinkColor = GetColor(brightness, brightness, brightness);

    for (int i = 0; i < MENU_MAX; i++)
    {
        int y = baseY + i * 50;

        if (i == cursor)
        {
            // 選択バー画像
            DrawRotaGraph(
                baseX + 80,   // 中心X
                y + 10,       // 中心Y
                0.5,          // ← 半分サイズ
                0.0,
                selectBarHandle,
                TRUE
            );

            // ===== プレイヤーアニメ =====
            int frame = playerAnim.GetFrame();
            int handle = playerRun.Get(frame);

            DrawRotaGraph(
                baseX - 60,   // メニューの左
                y ,
                0.7,
                0.0,
                handle,
                TRUE
            );


            //セレクト中は点滅
               DrawString(baseX, y, menu[i], blinkColor);

        }
        else
        {
            DrawString(baseX, y, menu[i], GetColor(255, 255, 255));
        }

        int idleFrame = playerIdleAnim.GetFrame();
        int idleHandle = playerIdle.Get(idleFrame);

        // 左の大きいスペース
        int playerX = 200;
        int playerY = 350;

        // ===== プレイヤー待機モーション =====
        DrawRotaGraph(
            playerX,
            playerY,
            2.0,
            0.0,
            idleHandle,
            TRUE
        );

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