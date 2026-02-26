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

void MushroomReg::Update()
{
    x += speed * dir;

    // âÊñ í[Ç≈îΩì]ÅiâºÅj
    if (x < 0)
        dir = 1;

    if (x > 640 - 32)
        dir = -1;

    anim.Update();
}

void MushroomReg::Draw()
{
    int frame = anim.GetFrame();
    int handle = sprite.Get(frame);

    double scaleX = (dir == 1) ? 1.0 : -1.0;

    DrawRotaGraph(
        (int)x + 16,
        (int)y + 16,
        1.0,
        0.0,
        handle,
        TRUE,
        FALSE,
        scaleX
    );
}

Rect MushroomReg::GetRect() const
{
    return {
        x,
        y,
        x + 32,
        y + 32
    };
}