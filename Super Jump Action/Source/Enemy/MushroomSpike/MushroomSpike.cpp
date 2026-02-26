#include "MushroomSpike.h"
#include "DxLib.h"

MushroomSpike::MushroomSpike(float startX, float startY)
{
    x = startX;
    y = startY;

    hp = 1;

    // スプライトシート読み込み
    sprite.Load("Mushroom_spike.png", 10, 5, 32, 32);

    // 歩行アニメ（2列目・9枚)
    int walkStart = walkRow * divX;     // row1 → 10
    int walkEnd = walkStart + 8;      // 9枚

    walkAnim.Start(walkStart, walkEnd, 5, true);

    // トゲアニメ（4列目・10枚）
    int spikeStart = spikeRow * divX;   // row3 → 30
    int spikeEnd = spikeStart + 9;    // 10枚

    spikeAnim.Start(spikeStart, spikeEnd, 4, true);
}

void MushroomSpike::Update(bool playerIsJumping)
{
    spikeActive = playerIsJumping;

    if (!spikeActive)
    {
        // 通常歩行
        x += speed * dir;

        // 画面端で反転
        if (x < 0)
            dir = 1;

        if (x > 640 - 32)
            dir = -1;

        walkAnim.Update();
    }
    else
    {
        // トゲ展開（停止
        spikeAnim.Update();
    }
}

void MushroomSpike::Draw()
{
    int frame;

    if (spikeActive)
        frame = spikeAnim.GetFrame();
    else
        frame = walkAnim.GetFrame();

    int handle = sprite.Get(frame);

    int turnFlag = (dir == -1) ? TRUE : FALSE;

    DrawRotaGraph2(
        (int)x + 16,
        (int)y + 16,
        16,
        16,
        1.0,
        0.0,
        handle,
        TRUE,
        turnFlag
    );
}

Rect MushroomSpike::GetRect() const
{
    return {
        x,
        y,
        x + 32,
        y + 32
    };
}