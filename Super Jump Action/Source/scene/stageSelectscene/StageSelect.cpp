#include "StageSelect.h"
#include "DxLib.h"

// シーン関連
#include "../sceneManager.h"
#include "../../scene/gameScene/gameScene.h"
#include "../../scene/title/titleScene.h"


void StageSelectScene::Init()
{
    cursor = 0;
    inputWait = 10;
    blinkTimer = 0;
}

void StageSelectScene::Update()
{
    input.Update();

    if (inputWait > 0)
    {
        inputWait--;
        input.LateUpdate();
        return;
    }

    blinkTimer++;

    // ↓キー
    if (input.IsKeyDownTrigger(KEY_INPUT_DOWN))
    {
        cursor++;
        if (cursor >= STAGE_MAX)
            cursor = 0;
    }

    // ↑キー
    if (input.IsKeyDownTrigger(KEY_INPUT_UP))
    {
        cursor--;
        if (cursor < 0)
            cursor = STAGE_MAX - 1;
    }

    // 決定
    if (input.IsKeyDownTrigger(KEY_INPUT_RETURN))
    {
        SceneManager::ChangeScene(new GameScene(cursor));
        return;
    }

    // 戻る
    if (input.IsKeyDownTrigger(KEY_INPUT_ESCAPE))
    {
        SceneManager::ChangeScene(new TitleScene());
        return;
    }

    input.LateUpdate();
}

void StageSelectScene::Draw()
{
    // タイトル
    DrawString(300, 100, "STAGE SELECT", GetColor(255, 255, 255));

    const char* stageNames[STAGE_MAX] =
    {
        "TUTORIAL",
        "STAGE 1",
        "STAGE 2",
        "STAGE 3"
    };


    int baseX = 500;
    int baseY = 250;

    // 点滅
    float t = sin(blinkTimer * 0.1f);
    int brightness = 120 + (int)(t * 60);
    int blinkColor = GetColor(brightness, brightness, brightness);

    for (int i = 0; i < STAGE_MAX; i++)
    {
        int y = baseY + i * 60;

        if (i == cursor)
        {
            DrawString(baseX, y, stageNames[i], blinkColor);
        }
        else
        {
            DrawString(baseX, y, stageNames[i], GetColor(255, 255, 255));
        }
    }
}

void StageSelectScene::End()
{
}