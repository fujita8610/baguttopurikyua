#pragma once
#include "../EnemyBase/EnemyBase.h"
#include "../../Animation/Animation.h"
#include "../../Graphics/SpriteSheet.h"

//
#include "../../GameDebug/GameDebug.h"

class MushroomReg : public EnemyBase
{
public:
    MushroomReg(float startX, float startY);

    void Update(const Player& player) override;
    void Draw(float camX, float camY) override;
    Rect GetRect() const override;

private:
    SpriteSheet sprite;
    Animation anim;

    int row = 1;   // 使う行（例：2行目）
    int divX = 10; // 横分割数

    float speed = 2.0f;
    int dir = 1;

    float scale = 2.0f;

    int width = 32;
    int height = 32;

    int hitWidth = 28;
    int hitHeight = 28;
};