#include "MushroomReg.h"
#include "DxLib.h"

MushroomReg::MushroomReg(float startX, float startY)
{
    x = startX;
    y = startY;

    sprite.Load("Data/Enemy/Enemy Mushrooms/Mushroom_Reg.png", 10, 5, 32, 32);

    int start = row * divX;
    int end = start + 8;

    anim.Start(start, end, 5, true);
}

void MushroomReg::Update(const Player& player)
{
    x += speed * dir;

    // 画面端で反転（仮）
    if (x < 0)
        dir = 1;

    if (x > 640 - 32)
        dir = -1;

    anim.Update();
}

void MushroomReg::Draw(float camX, float camY)
{
    int frame = anim.GetFrame();
    int handle = sprite.Get(frame);

    double exRate = scale;
    double angle = 0.0;


    int turnFlag = (dir == -1) ? TRUE : FALSE;

    int drawX = (int)(x - camX);
    int drawY = (int)(y - camY);


    DrawRotaGraph2(
        drawX + 16,
        drawY,
        16,              // 中心X
        16,              // 中心Y
        exRate,
        angle,
        handle,
        TRUE,
        turnFlag
    );

    // デバッグ当たり判定
    if (GameDebug::IsDebug())
    {
        Rect r = GetRect();

        DrawBox(
            (int)(r.left - camX),
            (int)(r.top - camY),
            (int)(r.right - camX),
            (int)(r.bottom - camY),
            GetColor(255, 0, 0),
            FALSE
        );
    }
}

Rect MushroomReg::GetRect() const
{
    return {
        x,
        y,
        x + hitWidth,
        y + hitHeight
    };
}