#include "tutorial.h"
#include "DxLib.h"

void TutorialManager::Init(bool enableTutorial)
{
    enabled = enableTutorial;

    active = false;
    step = 0;
}

bool TutorialManager::IsActive() const
{
    return active;
}

void TutorialManager::Update(const Player& player, Input& input)
{
    if (!enabled) return;

    // チュートリアル開始位置
    if (!active && step == 0)
    {
        if (player.GetX() > 300)
        {
            active = true;
            step = 1;
        }
    }

    if (active)
    {
        if (input.IsKeyDown(KEY_INPUT_SPACE))
        {
            active = false;
            step++;
        }
    }
}

void TutorialManager::Draw()
{
    if (!active) return;

    DrawBox(100, 100, 900, 300, GetColor(0, 0, 0), TRUE);

    switch (step)
    {
    case 1:
        DrawString(
            120,
            150,
            "A,Dキーで移動できます",
            GetColor(255, 255, 255));
        break;

    case 2:
        DrawString(
            120,
            150,
            "SPACEキーでジャンプ",
            GetColor(255, 255, 255));
        break;
    }

    DrawString(
        120,
        250,
        "SPACEで続行",
        GetColor(255, 255, 0));
}