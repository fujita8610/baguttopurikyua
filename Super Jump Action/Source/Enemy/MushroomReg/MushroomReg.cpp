#include "MushroomReg.h"
#include "DxLib.h"
#include "../../map/map.h"
#include "../../map/tileManager/tileManager.h"

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

    // 実際のタイルサイズ = 8 × 4 = 32
    const int actualTileSize = TILE_SIZE * SCALE;

    // 進行方向の前端のタイル座標を取得
    int checkX;
    if (dir == 1)
        checkX = (int)(x + hitWidth) / actualTileSize;  // 右端
    else
        checkX = (int)(x) / actualTileSize;              // 左端

    int checkY = (int)(y + hitHeight / 2) / actualTileSize;  // 中心Y

    if (IsWall(checkX, checkY))
    {
        dir *= -1;
        x -= speed * dir * 2;  // めり込み解消
    }

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